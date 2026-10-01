#include "logging/Logger.h"

int main() {

    Logger logger("logs/gateway.log");

    logger.info("Gateway started");
    logger.warning("Low soil moisture detected");
    logger.error("Sensor connection failed");

    return 0;
}
