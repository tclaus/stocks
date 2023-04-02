//
// Created by Thorsten Claus on 02.04.23.
//

#ifndef STOCKS_SELECTIONOFSYMBOLS_H
#define STOCKS_SELECTIONOFSYMBOLS_H

#include <map>

/**
 * While the user in in search mode, he/she can select or deselect any symbols in the results.
 * That means any symbol that is already in the portfolio list might be deselected if found in a search again.
 * The list consists then of a list of symbols that are selected - with a true value or deselected with a false value.
 * The users portfolio then is updated with new or to be removed symbols.
 */
class SelectionOfSymbols {
public:
    SelectionOfSymbols();

    ~SelectionOfSymbols();

    /**
     * The list is initialized with existing symbols from the portfolio. Any existing symbol is marked with a true value.
     * Toggling means to select (true) or deselect any symbol.
     * If a symbol does not exist in the list, it is added.
     * @param symbol
     */
    void ToggleUserSelection(const char &symbol);

    /**
     * Empties the list.
     */
    void Clear();

private:
    std::map<char, bool> *fUsersSelectionOfSymbols;
};


#endif //STOCKS_SELECTIONOFSYMBOLS_H
