#!/bin/bash

echo "=========================================="
echo " Smart Agriculture Gateway Integration Test"
echo "=========================================="

LOG_FILE="logs/gateway.log"

echo "[1/4] Preparing gateway log..."
mkdir -p logs
: > "$LOG_FILE"

echo "[2/4] Starting gateway..."
./bin/smart_gateway > /tmp/smart_gateway_output.log 2>&1 &
GATEWAY_PID=$!

sleep 5

echo "[3/4] Sending telemetry from 3 sensor nodes..."
./test_tcp_client

echo "Waiting for gateway to process all nodes..."

for i in {1..10}; do
    NODE1=$(grep -c "Telemetry received: NODE_01" "$LOG_FILE")
    NODE2=$(grep -c "Telemetry received: NODE_02" "$LOG_FILE")
    NODE3=$(grep -c "Telemetry received: NODE_03" "$LOG_FILE")

    if [ "$NODE1" -ge 1 ] && [ "$NODE2" -ge 1 ] && [ "$NODE3" -ge 1 ]; then
        break
    fi

    sleep 1
done

echo "[4/4] Stopping gateway..."
kill "$GATEWAY_PID" 2>/dev/null
wait "$GATEWAY_PID" 2>/dev/null

echo "Checking gateway results..."

PASS=true

grep -q "Telemetry received: NODE_01" "$LOG_FILE" || PASS=false
grep -q "Telemetry received: NODE_02" "$LOG_FILE" || PASS=false
grep -q "Telemetry received: NODE_03" "$LOG_FILE" || PASS=false

if [ "$PASS" = true ]; then
    echo
    echo "=========================================="
    echo " INTEGRATION TEST PASSED"
    echo "=========================================="
    echo "NODE_01 telemetry received: PASS"
    echo "NODE_02 telemetry received: PASS"
    echo "NODE_03 telemetry received: PASS"
    echo "Multi-node telemetry reception: PASS"
    exit 0
else
    echo
    echo "=========================================="
    echo " INTEGRATION TEST FAILED"
    echo "=========================================="
    echo "=========================================="
    echo
    echo "Gateway log:"
    cat "$LOG_FILE"
    echo
    echo "Gateway output:"
    cat /tmp/smart_gateway_output.log
    exit 1
fi
