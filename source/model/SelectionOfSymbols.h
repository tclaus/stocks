//
// Created by Thorsten Claus on 02.04.23.
//

#ifndef STOCKS_SELECTIONOFSYMBOLS_H
#define STOCKS_SELECTIONOFSYMBOLS_H

#include <map>
#include <clocale>
#include <string>
#include <list>

/**
 * While the user in in search mode, he/she can select or deselect any symbols in the results.
 * That means any symbol that is already in the portfolio fList might be deselected if found in a search again.
 * The fList consists then of a fList of symbols that are selected - with a true value or deselected with a false value.
 * The users portfolio then is updated with new or to be removed symbols.
 */
class SelectionOfSymbols {
public:
    SelectionOfSymbols();

    ~SelectionOfSymbols();

    /**
     * The fList is initialized with existing symbols from the portfolio. Any existing symbol is marked with a true value.
     * Toggling means to select (true) or deselect any symbol.
     * If a symbol does not exist in the fList, it is added.
     * @param symbol
     */
    void ToggleUserSelection(const std::string &symbol);

    /**
     * Empties the fList.
     */
    void Clear();

    /**
     * Returns a list of newly selected symbols.
     * @return A {@link BList}
     */
    std::list<std::string> *ListToBeAdded();

    /**
     * Returns a list of symbols to be removed.
     * @return A {@link BList}
     */
    std::list<std::string> *ListToBeRemoved();

private:
    std::map<std::string, bool> *fUsersSelectionOfSymbols;
};

#endif //STOCKS_SELECTIONOFSYMBOLS_H
