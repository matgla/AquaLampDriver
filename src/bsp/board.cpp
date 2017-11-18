#include "bsp/board.hpp"

#include "hal/core/backupRegisters.hpp"
#include "hal/core/core.hpp"

namespace bsp
{

Board::Board()
    : registers(hal::core::BackupRegisters::get()),
      logger_("Board")
{
    hal::core::Core::initializeClocks();
    logger_.info() << "Initialized";
}

} // namespace bsp
