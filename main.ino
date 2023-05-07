#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "xxxxxxxxx";
const char* password = "xxxxx";

const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
            <style>
                    body{
                font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
                background-color: gray;
                max-width: 800px;
                min-width: 320px;
                margin: 0 auto;
                padding: 0px;
                text-align: center;
                height: auto;}
            h2{
                margin: 0px;
                padding-top: 10px;
                color: white;}
            .menu{
                height: 70px;
                background-color: rgb(0, 0, 155);}   

            h4{
                padding-top: 5px;}
            h5{
                padding-left: 50px;
                margin: 8px;
                text-align: left;}
            .tag{
                text-align: right;
                width: 30%;
                float: left;
                margin: 8px;
                text-align: center;}
            .block{
                width: 100%;
                height: 100%;
                display: inline-block;
                text-align: center;}
            .Container_info{
                width: 100%;
                border-radius: 15px;
                background-color: rgb(214, 14, 14);}
            .P-L{
                width: 70%;
                float: left;
                height: 100px;}
            .P-R{
                width: 30%;
                float: right;
                height: 100px;}
            .container_L, .Container_R{
                width: 49%;
                border-radius: 15px;
                background-color: rgb(105, 105, 105);
                display: inline-block;}
            .switch {
                position: relative; 
                display: inline-block; 
                width: 90px; 
                height: 54px} 
            .switch input {
                display: none}
            .slider {
                position: absolute; 
                top: 0; 
                left: 0; 
                right: 0; 
                bottom: 0; 
                background-color: #ccc; 
                border-radius: 6px}
            .slider:before {
                position: absolute; 
                content: ""; 
                height: 39px; 
                width: 39px; 
                left: 8px; 
                bottom: 8px; 
                background-color: #fff; 
                -webkit-transition: .4s; 
                transition: .4s; 
                border-radius: 3px}
            input:checked+.slider {
                background-color: rgb(15, 24, 156)}
            input:checked+.slider:before {
                -webkit-transform: translateX(34px); 
                -ms-transform: translateX(34px); 
                transform: translateX(34px)}
  </style>

<body>
    <main>
        <div class="menu">
            <h2>AUTOMAÇÃO - ESP32</h2>
        </div>
        <div class="block">
            <div class="container_info">
                <div class="P-L">
                    <h3>Notificações</h3>
                </div>
                <div class="P-R">MODE AUTO<br>
                    <label class="switch">
                        <input type="checkbox" onchange="toggleCheckbox(this)" id="" + outputState()>
                    <span class="slider round"></span>
                </label>
                </div>
            </div>
            <div class="container_L">
                <h4><div class="tag">GPIO 15</div>
                    <label class="switch">
                        <input type="checkbox" onchange="toggleCheckbox(this)" id="15" + outputState(15)>
                    <span class="slider round"></span>
                </label>
                </h4>
                
                
                <h4><div class="tag">GPIO 02</div>
                    <label class="switch">
                        <input type="checkbox" onchange="toggleCheckbox(this)" id="2" + outputState(2)>
                    <span class="slider round"></span>
                </label>
                </h4>
                <h4><div class="tag">GPIO 04</div>
                    <label class="switch">
                        <input type="checkbox" onchange="toggleCheckbox(this)"id="4" + outputState(4)>
                    <span class="slider round"></span>
                </label>
                </h4>
                <h4><div class="tag">GPIO 13</div>
                    <label class="switch">
                        <input type="checkbox" onchange="toggleCheckbox(this)"id="13" + outputState(13)>
                    <span class="slider round"></span>
                </label>
                </h4>   
            </div>
            <div class="Container_R">
                <h4><div class="tag">GPIO 12</div>
                    <label class="switch">
                        <input type="checkbox" onchange="toggleCheckbox(this)"id="12" + outputState(12)>
                    <span class="slider round"></span>
                </label>
                </h4>
                
                
                <h4><div class="tag">GPIO 14</div>
                    <label class="switch">
                        <input type="checkbox" onchange="toggleCheckbox(this)" id="14"+ outputState(14) +>
                    <span class="slider round"></span>
                </label>
                </h4>
                <h4><div class="tag">GPIO 27</div>
                    <label class="switch">
                        <input type="checkbox" onchange="toggleCheckbox(this)"id="27" + outputState(27)>
                    <span class="slider round"></span>
                </label>
                </h4>
                <h4><div class="tag">GPIO 33</div> 
                    <label class="switch">
                    <input type="checkbox" onchange="toggleCheckbox(this)"id="33" + outputState(33)>
                    <span class="slider round"></span>
                </label>
                </h4>
                    
            </div>
            <div class="container_sensor">
                <h3>SENSORES</h3>
                    <h5>H2O</h5>
                    <h5>Umidade</h5>
                    <h5>Temp.</h5>  
            </div>
        </div>
    </main>
<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  
    if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
  
     else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
     xhr.send();
}
</script>
</body>
</html>
)rawliteral";

String outputState(int output){
    if(digitalRead(output)){
      return "checked";
    }
    else {
      return "";
    }
  }
  
  void setup(){
    // Serial port for debugging purposes
    Serial.begin(115200);
    
    pinMode(15, OUTPUT);
    digitalWrite(15, LOW);
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
    pinMode(14, OUTPUT);
    digitalWrite(14, LOW);
    pinMode(27, OUTPUT);
    digitalWrite(27, LOW);
    pinMode(33, OUTPUT);
    digitalWrite(33, LOW);
    
    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi..");
    }
  
    // Print ESP Local IP Address
    Serial.println(WiFi.localIP());
  
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/html", index_html);
    });
  
    // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
      String inputMessage1;
      String inputMessage2;
      // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
      if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
        inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
        inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
        digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
      }
      else {
        inputMessage1 = "No message sent";
        inputMessage2 = "No message sent";
      }
      Serial.print("GPIO: ");
      Serial.print(inputMessage1);
      Serial.print(" - Set to: ");
      Serial.println(inputMessage2);
      request->send(200, "text/plain", "OK");
    });
  
    // Start server
    server.begin();
  }
  
  void loop() {
  
  }
