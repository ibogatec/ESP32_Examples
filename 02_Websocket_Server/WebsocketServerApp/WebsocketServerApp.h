#pragma once

uint16_t constexpr WEBSOCKET_TASK_STACK_SIZE{ 4096 };
uint8_t  constexpr WEBSOCKET_TASK_PRIORITY  { tskIDLE_PRIORITY };
uint8_t  constexpr WEBSOCKET_TASK_CORE_ID   { 0 };

void WebSocketAppStart();
