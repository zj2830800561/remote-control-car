/*
 * 智能语言控制控制，支持天猫、小爱、小度、google Assistent同时控制
 * 2021-08-12
 * QQ交流群：566565915
 * 官网https://bemfa.com 
 */
#include <ESP8266WiFi.h>

#define TCP_SERVER_ADDR "bemfa.com" //巴法云服务器地址默认即可
#define TCP_SERVER_PORT "8344" //服务器端口，tcp创客云端口8344

//********************需要修改的部分*******************//

#define DEFAULT_STASSID  "辅导员在后门看你"     //WIFI名称，区分大小写，不要写错
#define DEFAULT_STAPSW   "qwertyuiop."  //WIFI密码
String UID = "326b9e9ceadce1dcc3853668e317ce42";  //用户私钥，可在控制台获取,修改为自己的UID
String TOPIC = "xiaoche";         //主题名字，可在控制台新建 
             //单片机LED引脚值，D2是NodeMcu引脚命名方式，其他esp8266型号将D2改为自己的引脚

//**************************************************//
//最大字节数
#define MAX_PACKETSIZE 512
//设置心跳值30s
#define KEEPALIVEATIME 30*1000
//tcp客户端相关初始化，默认即可
WiFiClient TCPclient;
String TcpClient_Buff = "";//初始化字符串，用于接收服务器发来的数据
unsigned int TcpClient_BuffIndex = 0;
unsigned long TcpClient_preTick = 0;
unsigned long preHeartTick = 0;//心跳
unsigned long preTCPStartTick = 0;//连接
bool preTCPConnected = false;
//相关函数初始化
//连接WIFI
void doWiFiTick();
void startSTA();

//TCP初始化连接
void doTCPClientTick();
void startTCPClient();
void sendtoTCPServer(String p);

//引脚控制函数，具体函数内容见下方
void turnOn();        //开机   
void turnOff();       //关机
void middleSpeed();   //低速
void highSpeed();     //中高速
void turnForwardOn(); //开始前进
void turnForwardOff();//停止前进
void turnLeftOn();    //开始左转
void turnLeftOff();   //停止左转
void turnRightOn();   //开始右转
void turnRightOff();  //停止右转
void turnBackOn();    //开始倒车
void turnBackOff();   //停止倒车
void turnStop();      //停车
void turnBibi();      //喇叭




/*
  *发送数据到TCP服务器
 */
void sendtoTCPServer(String p){
  if (!TCPclient.connected()) 
  {
    Serial.println("Client is not readly");
    return;
  }
  TCPclient.print(p);
}


/*
  *初始化和服务器建立连接
*/
void startTCPClient(){
  if(TCPclient.connect(TCP_SERVER_ADDR, atoi(TCP_SERVER_PORT))){
    Serial.print("\nConnected to server:");
    Serial.printf("%s:%d\r\n",TCP_SERVER_ADDR,atoi(TCP_SERVER_PORT));
    
    String tcpTemp="";  //初始化字符串
    tcpTemp = "cmd=1&uid="+UID+"&topic="+TOPIC+"\r\n"; //构建订阅指令
    sendtoTCPServer(tcpTemp); //发送订阅指令
    tcpTemp="";//清空
    /*
     //如果需要订阅多个主题，可再次发送订阅指令
      tcpTemp = "cmd=1&uid="+UID+"&topic="+主题2+"\r\n"; //构建订阅指令
      sendtoTCPServer(tcpTemp); //发送订阅指令
      tcpTemp="";//清空
     */
    
    preTCPConnected = true;
    preHeartTick = millis();
    TCPclient.setNoDelay(true);
  }
  else{
    Serial.print("Failed connected to server:");
    Serial.println(TCP_SERVER_ADDR);
    TCPclient.stop();
    preTCPConnected = false;
  }
  preTCPStartTick = millis();
}


/*
  *检查数据，发送心跳
*/
void doTCPClientTick(){
 //检查是否断开，断开后重连
   if(WiFi.status() != WL_CONNECTED) return;
  if (!TCPclient.connected()) {//断开重连
  if(preTCPConnected == true){
    preTCPConnected = false;
    preTCPStartTick = millis();
    Serial.println();
    Serial.println("TCP Client disconnected.");
    TCPclient.stop();
  }
  else if(millis() - preTCPStartTick > 1*1000)//重新连接
    startTCPClient();
  }
  else
  {
    if (TCPclient.available()) {//收数据
      char c =TCPclient.read();
      TcpClient_Buff +=c;
      TcpClient_BuffIndex++;
      TcpClient_preTick = millis();
      
      if(TcpClient_BuffIndex>=MAX_PACKETSIZE - 1){
        TcpClient_BuffIndex = MAX_PACKETSIZE-2;
        TcpClient_preTick = TcpClient_preTick - 200;
      }
      preHeartTick = millis();
    }
    if(millis() - preHeartTick >= KEEPALIVEATIME){//保持心跳
      preHeartTick = millis();
      Serial.println("--Keep alive:");
      sendtoTCPServer("ping\r\n"); //发送心跳，指令需\r\n结尾，详见接入文档介绍
    }
  }
  if((TcpClient_Buff.length() >= 1) && (millis() - TcpClient_preTick>=200))
  {
    TCPclient.flush();
    Serial.print("Rev string: ");
    TcpClient_Buff.trim(); //去掉首位空格
    Serial.println(TcpClient_Buff); //打印接收到的消息
    String getTopic = "";
    String getMsg = "";
    if(TcpClient_Buff.length() > 15){//注意TcpClient_Buff只是个字符串，在上面开头做了初始化 String TcpClient_Buff = "";
          //此时会收到推送的指令，指令大概为 cmd=2&uid=xxx&topic=light002&msg=off
          int topicIndex = TcpClient_Buff.indexOf("&topic=")+7; //c语言字符串查找，查找&topic=位置，并移动7位，不懂的可百度c语言字符串查找
          int msgIndex = TcpClient_Buff.indexOf("&msg=");//c语言字符串查找，查找&msg=位置
          getTopic = TcpClient_Buff.substring(topicIndex,msgIndex);//c语言字符串截取，截取到topic,不懂的可百度c语言字符串截取
          getMsg = TcpClient_Buff.substring(msgIndex+5);//c语言字符串截取，截取到消息
          Serial.print("topic:------");
          Serial.println(getTopic); //打印截取到的主题值
          Serial.print("msg:--------");
          Serial.println(getMsg);   //打印截取到的消息值
   }
   /*
    *命令处理函数
    *
    *
   */
   if(getMsg  == "turnon"){            //开机    
     turnOn();
   }else if(getMsg  == "turnoff"){     //关机
     turnOff();
   }else if(getMsg  == "middlespeed"){ // 低速行驶
     middleSpeed();
   }else if(getMsg  == "highspeed"){   // 中高速行驶
     highSpeed();
   }else if(getMsg  == "forwardon"){   // 开始前进
     turnForwardOn();
   }else if(getMsg == "forwardoff"){   // 停止前进
     turnForwardOff();
   }else if(getMsg == "lefton"){  //  开始左转
     turnLeftOn();
   }else if(getMsg == "leftoff"){ //  停止左转
     turnLeftOff();
   }else if(getMsg == "righton"){ //  开始右转
     turnRightOn();
   }else if(getMsg == "rightoff"){//  停止右转
     turnRightOff();
   }else if(getMsg == "backwardon"){  //  开始倒车
     turnBackOn();
   }else if(getMsg == "backwardoff"){ //  停止倒车
     turnBackOff();
   }else if(getMsg == "allstop"){    // 刹车
     turnStop();
   }else if(getMsg == "bibi"){    // 喇叭
     turnBibi();
   }

   TcpClient_Buff="";
   TcpClient_BuffIndex = 0;
  }
}
/*
  *初始化wifi连接
*/
void startSTA(){
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(DEFAULT_STASSID, DEFAULT_STAPSW);
}



/**************************************************************************
                                 WIFI
***************************************************************************/
/*
  WiFiTick
  检查是否需要初始化WiFi
  检查WiFi是否连接上，若连接成功启动TCP Client
  控制指示灯
*/
void doWiFiTick(){
  static bool startSTAFlag = false;
  static bool taskStarted = false;
  static uint32_t lastWiFiCheckTick = 0;

  if (!startSTAFlag) {
    startSTAFlag = true;
    startSTA();
  }

  //未连接1s重连
  if ( WiFi.status() != WL_CONNECTED ) {
    if (millis() - lastWiFiCheckTick > 1000) {
      lastWiFiCheckTick = millis();
    }
  }
  //连接成功建立
  else {
    if (taskStarted == false) {
      taskStarted = true;
      Serial.print("\r\nGet IP Address: ");
      Serial.println(WiFi.localIP());
      startTCPClient();
    }
  }
}

void turnOn()
{
  Serial.println("Turn ON");
  digitalWrite(D0,HIGH);
}

void turnOff()
{
  Serial.println("Turn OFF");
  digitalWrite(D0,LOW);
  digitalWrite(D1,LOW);
  digitalWrite(D1,LOW);
  digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D4,LOW);
  digitalWrite(D5,LOW);
  digitalWrite(D6,LOW);
}

void middleSpeed(){
  Serial.println("SET MiddleSpeed");
  digitalWrite(D1,LOW);
}

void highSpeed(){
  Serial.println("SET HighSpeed");
  digitalWrite(D1,HIGH);  
}

void turnForwardOn(){
  Serial.println("Turn Forward");
  digitalWrite(D3,LOW);
  digitalWrite(D2,HIGH);
}
 
void turnForwardOff(){
  Serial.println("Turn StopForward");
  digitalWrite(D2,LOW);
}

void turnBackOn(){
  Serial.println("Turn Back");
  digitalWrite(D2,LOW);
  digitalWrite(D3,HIGH);

}

void turnBackOff(){
  Serial.println("Turn StopBack");
  digitalWrite(D3,LOW);
}

void turnLeftOn(){
  Serial.println("Turn Left");
  digitalWrite(D5,LOW);
  digitalWrite(D4,HIGH);
}

void turnLeftOff(){
  Serial.println("Turn StopLeft");
  digitalWrite(D4,LOW);
}

void turnRightOn(){
  Serial.println("Turn Right");
  digitalWrite(D4,LOW);
  digitalWrite(D5,HIGH);
}

void turnRightOff(){
  Serial.println("StopRight");
  digitalWrite(D5,LOW);
}

void turnStop(){
  Serial.println("ALL STOP!!!");
  digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D4,LOW);
  digitalWrite(D5,LOW);
}

void turnBibi(){
  Serial.println("BIBI!!!");
  digitalWrite(D6,HIGH); //喇叭响两面后关闭
  digitalWrite(D6,LOW);
  
}
// 初始化，相当于main 函数
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  digitalWrite(D0,LOW);
  digitalWrite(D1,LOW);
  digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D4,LOW);
  digitalWrite(D5,LOW);
  digitalWrite(D6,LOW);
  digitalWrite(LED_BUILTIN,LOW);
  Serial.println("Beginning...");
}

//循环
void loop() {
  doWiFiTick();
  doTCPClientTick();
}
