let websocket        = null;
let reconnectAttempt = 0;
let reconectInterval = undefined;
const websocketUrl   = "ws://192.168.4.1:1337";


function sendWSMessage(message) {
    if (websocket) {
        console.log(`Sending Web socket message: '${message}'`);
        websocket.send(message);
    }
}

function onWsOpen(event) {
    console.log("onWsOpen(): Connected to a Websocket Server");

    reconnectAttempt = 0;

    if (reconectInterval) {
        clearInterval(reconectInterval);
        reconectInterval = undefined;
    }

    // Enable button
    $("#toggle-led-button").attr("disabled", false);

    // Get the current state of the LED
    sendWSMessage("getLEDState");
}

function onWSClose(event) {
    console.log("onWsClose(): Disconnected from a Websocket Server");

    // Disable button
    $("#toggle-led-button").attr("disabled", true);

    // Try reconnect every 1 second, max 5 times
    reconectInterval = setInterval(() => {
        wsConnect(websocketUrl);
    }, 1000);

}

function onWSMessage(event) {
    console.log(`onWsMessage(): Message received: '${event.data}'`);

    // Update index.html with the LED state
    switch (event.data) {
        case "OFF":
            $("#led-status").css("background-color", "lightgray");
            $("#toggle-led-button").val("Turn LED: ON");
            break;

        case "ON":
            $("#led-status").css("background-color", "red");
            $("#toggle-led-button").val("Turn LED: OFF");
            break;

        default:
            break;
    }
}

function onWSError(event) {
    console.error(`onWSError(): ERROR: '${event.data}'`);
}

function wsConnect() {
    reconnectAttempt += 1;
    
    if (reconnectAttempt >= 5 && reconectInterval) {
        clearInterval(reconectInterval);
        reconectInterval = undefined;
    }

    // Connect to a websocket server
    websocket = new WebSocket(websocketUrl);

    // Assign callbacks
    if (websocket) {
        websocket.onopen    = onWsOpen;
        websocket.onclose   = onWSClose;
        websocket.onmessage = onWSMessage;
        websocket.onerror   = onWSError;
    }
}

$(document).ready(function() {

    // Connect to a websocket server
    wsConnect();
});
