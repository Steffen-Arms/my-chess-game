#ifndef UCI_INTERFACE_H
#define UCI_INTERFACE_H

#include "move.h"
#include <optional>
#include <string>

std::string toUci(const Move& m);
std::optional<Move> fromUci(Board& board, std::string_view uci_move);
void uciLoop();

#endif
