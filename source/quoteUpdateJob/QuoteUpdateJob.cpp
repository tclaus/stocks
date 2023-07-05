//
// Created by Thorsten Claus on 28.04.23.
//

#include "QuoteUpdateJob.h"
#include "Portfolio.h"
#include "ApiBuilder.h"
#include "QuoteRequestStore.h"

QuoteUpdateJob::QuoteUpdateJob(BHandler *handler) {
    ApiBuilder apiBuilder = ApiBuilder();
    fStockConnector = apiBuilder.CreateStockConnector(handler);
}

void
QuoteUpdateJob::ExecuteJob() {
    UpdateLoop();
}

void
QuoteUpdateJob::UpdateLoop() {
    printf("QuoteUpdateJob: Starting update loop.\n");
    while (!ShouldStopThread()) {
        std::this_thread::sleep_for(fDelayBeforeNextLoop);
        CheckQuotesToUpdate();
    }
}

void
QuoteUpdateJob::CheckQuotesToUpdate() {

    Portfolio &portfolio = Portfolio::Instance();
    for (auto const &quote: *portfolio.List()) {
        if (IsQuoteUpdateExpired(*quote) && !IsQuoteUpdateInProgress(*quote)) {
            printf("Requesting update for quote: %s\n", quote->symbol->String());
            RequestUpdateQuoteDetails(quote);
        }
    }
}

void QuoteUpdateJob::RequestUpdateQuoteDetails(Quote *const &quote) {
    quote->isWaitingForRequest = true;
    int quoteRequestId = fStockConnector->RetrieveQuote(quote->symbol->String());
    QuoteRequestStore &quoteRequestStore = QuoteRequestStore::Instance();
    quoteRequestStore.AddQuoteRequestId(quoteRequestId, *quote);
}

bool
QuoteUpdateJob::IsQuoteUpdateExpired(Quote &quote) {
    timePoint now = std::chrono::high_resolution_clock::now();
    return ((quote.GetLastUpdatedTimePoint() + fUpdateCycleTime) < now);
}

bool
QuoteUpdateJob::IsQuoteUpdateInProgress(Quote &quote) {
    return quote.isWaitingForRequest;
}