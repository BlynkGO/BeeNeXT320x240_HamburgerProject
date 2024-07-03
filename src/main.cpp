#include <BlynkGOv3.h>

IMG_DECLARE(img_bg);
IMG_DECLARE(img_cat1);
IMG_DECLARE(img_cat2);
IMG_DECLARE(img_cat3);
IMG_DECLARE(img_cat4);
IMG_DECLARE(img_cat5);
IMG_DECLARE(img_cat6);

GLabel A0labCancel;

GImage background(img_bg);  //ตั้งตัวแปร background เป็นรูป img_bg
GImage cat1(img_cat1);
GImage cat2(img_cat2);
GImage cat3(img_cat3);
GImage cat4(img_cat4);
GImage cat5(img_cat5);
GImage cat6(img_cat6);

int    varMCat = 0;
int    varCatRun = 0;         // ตัวแปรสำหรับทดสอบแสดงผล เลขรัน
GRect  recCat;
unsigned long period = 100; //ความเร็ว
unsigned long last_time = 0;

FONT_DECLARE(phethai_100);  //โหลดฟอนต์
int IntCancel = 20;
IMG_DECLARE(img_ham1_1);
IMG_DECLARE(img_ham1_2);
IMG_DECLARE(img_ham2_1);
IMG_DECLARE(img_ham2_2);
IMG_DECLARE(img_ham5_1);
IMG_DECLARE(img_ham3_1);
IMG_DECLARE(img_ham3_2);
IMG_DECLARE(img_ham4_1);
IMG_DECLARE(img_ham4_2);
GRect RApp1;
GImage  App[8];  //สร้างหน้า App

// App2-4
GImageButton btn_ham2_1(img_ham2_1);
GImageButton btn_ham2_2(img_ham2_2);
GImageButton btn_ham3_1(img_ham3_1);
GImageButton btn_ham3_2(img_ham3_2);
GImageButton btn_ham4_1(img_ham4_1);
GImageButton btn_ham4_2(img_ham4_2);


// App5
GButton A5btnPay;
GLabel labPro[6] ;
GLabel labPrice[6];

int16_t intTotal = 0 ;
int16_t intGTotal;

// App6;
GQRCode qrcode;
GButton A6btn;
GLabel A6labPay;
GLabel A6labPayTxt;
// App7

GImage ham[9];
int ProHam = 0;
GButton BtnApp7;

// --------------------------------------------------- จบประกาศตัวแปร
void close_App()
{
  for(int i = 0; i < 8; i++) {
    App[i].show(0);
  }
  BtnApp7.show(0);
  RApp1.show(0);
}

void CancelClicked()
{
  qrcode.onClicked([](GWIDGET) {        //ถ้ากดปุ่ม ตั้งค่า
    IntCancel = 20;
    A0labCancel = IntCancel;
  });
}

void Run_App7()    // App7 ประกอบแฮมเบอเกอ
{
  static SoftTimer timerHam;
  timerHam.setInterval(100, []() {
    if(ProHam < 120) {
      ProHam++;  //ขนาดหน้าไม่เกิน 320x240
      A0labCancel = ProHam;
    }
    else {
      A0labCancel = ProHam;
      timerHam.del();
      BtnApp7.show(1);
    }

    for(int r = 0; r <= 5; r++) {
      ham[r].show(1);
    }
    ham[0].align(ALIGN_BOTTOM, 0, -20);     //ขนมปัง
    ham[1].align(ALIGN_BOTTOM_LEFT, ProHam - 10, -20); //ไส้ 1
    ham[2].align(ALIGN_TOP_RIGHT, -ProHam, ProHam - 10);
    ham[3].align(ALIGN_BOTTOM_RIGHT, 10 - ProHam, -20);
    ham[4].align(ALIGN_TOP_LEFT, ProHam - 10, ProHam);
    ham[5].align(ALIGN_TOP, 0, ProHam - 8); //ขนมปัง
  });
}//จบประกอบham

void catShow()
{
  cat1.show(false);
  cat2.show(false);
  cat3.show(false);
  cat4.show(false);
  cat5.show(false);
  cat6.show(false);
}

void catRun()
{
  static SoftTimer timerCat;
  timerCat.setInterval(100, []() {
    if(varCatRun < 8) {
      varCatRun++ ;
      varMCat++;
    }
    if(varCatRun == 7)  {
      varCatRun = 1;  //เปลี่ยนรูปแมว
    }
    if(varMCat == 345)  {
      varMCat = 1;  //แมวขนาด 50x40 จอ 320x240
    }

    cat1.align(recCat, ALIGN_CENTER);
    cat2.align(recCat, ALIGN_CENTER);
    cat3.align(recCat, ALIGN_CENTER);
    cat4.align(recCat, ALIGN_CENTER);
    cat5.align(recCat, ALIGN_CENTER);
    cat6.align(recCat, ALIGN_CENTER);
    recCat.size(1, 1);   //ขนาด
    if(varCatRun == 1)  {
      catShow();
      cat1.show(true);
    }
    if(varCatRun == 2)  {
      catShow();
      cat2.show(true);
    }
    if(varCatRun == 3)  {
      catShow();
      cat3.show(true);
    }
    if(varCatRun == 4)  {
      catShow();
      cat4.show(true);
    }
    if(varCatRun == 5)  {
      catShow();
      cat5.show(true);
    }
    if(varCatRun == 6)  {
      catShow();
      cat6.show(true);
    }
    recCat.align(ALIGN_BOTTOM_LEFT, 1 + varMCat, -25); //กำหนดทิศทางแมววิ่ง


  });
} // จบ catRun

// ------------------------------------------------ จบฟังชั่น

void setup()
{
  Serial.begin(115200);
  Serial.println();
  BlynkGO.begin();
  A0labCancel = IntCancel;
  catRun();

  for(int i = 0; i < 8; i++) {
    App[i].size(320, 240); //ขนาดหน้าไม่เกิน 320x240
    App[i].align(ALIGN_TOP);
    App[i] = img_bg;  //(องศาสี0--360,ความสว่าง,ความเข้ม)
  }



  static SoftTimer timer;
  timer.setInterval(1000, []() {
    if(IntCancel > 10) {
      IntCancel--;
      A0labCancel = IntCancel;
      A0labCancel.font(prasanmit_30, TFT_RED);
      A0labCancel.align(ALIGN_TOP_RIGHT);
    }

    else {
      IntCancel--;
      A0labCancel = IntCancel;
      A0labCancel.font(phethai_100, TFT_RED);
      A0labCancel.align(ALIGN_CENTER);
      if(IntCancel < 1) {
        timer.pause();   //พัก
        //timer.del();  //เมื่อนับถึง 0 แล้วปิด timer
        A0labCancel.font(prasanmit_30, TFT_BLUE);
        A0labCancel = "กดหน้าจอ เพื่อสั่งสินค้า";
        RApp1.show(true);
      }

    }
  }); // จบ timer

  for(int l = 0; l <= 5; l++) {
    labPro[l].parent(App[5]);
    labPro[l].font(prasanmit_30, TFT_RED);
    labPrice[l].parent(App[5]);
    labPrice[l].font(prasanmit_30, TFT_RED);
  }
  // สร้าง App1
  RApp1.color(TFT_YELLOWBLYNK);
  RApp1.onClicked([](GWIDGET) {
    RApp1.show(0);
    App[2].show(1);
    IntCancel = 21;
    timer.replay(); //เริ่มทำงาน
  });

  // สร้าง App2
  btn_ham2_1.parent(App[2]);
  btn_ham2_1.align(ALIGN_LEFT, 30, 0);
  btn_ham2_2.parent(App[2]);
  btn_ham2_2.align(ALIGN_RIGHT, -30, 0);

  btn_ham2_1.onClicked([](GWIDGET) {
    App[3].show(true);
    labPrice[2] = 35;
    intTotal = 35;
    IntCancel = 20;
    labPrice[5] = intTotal;
    labPro[2] = "เนื้อ";
    ham[2] = img_ham2_1;

  });

  btn_ham2_2.onClicked([](GWIDGET) {
    App[3].show(true);
    labPrice[2] = 25;
    intTotal = 25;
    IntCancel = 30;
    labPrice[5] = intTotal;
    labPro[2] = "ปลา";
    ham[2] = img_ham2_2;
  });

  // สร้าง App3
  btn_ham3_1.parent(App[3]);
  btn_ham3_1.align(ALIGN_LEFT, 30, 0);
  btn_ham3_2.parent(App[3]);
  btn_ham3_2.align(ALIGN_RIGHT, -30, 0);

  btn_ham3_1.onClicked([](GWIDGET) {
    App[4].show(true);
    labPrice[3] = 25;
    intTotal = intTotal + 25;
    IntCancel = 20;
    labPrice[5] = intTotal;
    labPro[3] = "เบคอน";
    ham[3] = img_ham3_1;

  });

  btn_ham3_2.onClicked([](GWIDGET) {
    App[4].show(true);
    labPrice[3] = 15;
    intTotal = intTotal + 15;
    IntCancel = 20;
    labPrice[5] = intTotal;
    labPro[3] = "ไข่ดาว";
    ham[3] = img_ham3_2;
  });



  // สร้าง App4
  btn_ham4_1.parent(App[4]);
  btn_ham4_1.align(ALIGN_LEFT, 30, 0);
  btn_ham4_2.parent(App[4]);
  btn_ham4_2.align(ALIGN_RIGHT, -30, 0);

  btn_ham4_1.onClicked([](GWIDGET) {
    App[5].show(true);
    labPrice[4] = 15;
    intTotal = intTotal + 15;
    IntCancel = 20;
    labPrice[5] = intTotal;
    labPro[4] = "ชีส";
    ham[4] = img_ham4_1;

  });

  btn_ham4_2.onClicked([](GWIDGET) {
    App[5].show(true);
    labPrice[4] = 10;
    intTotal = intTotal + 10;
    IntCancel = 20;
    labPrice[5] = intTotal;
    labPro[4] = "เห็ด";
    ham[4] = img_ham4_2;
  });


  // สร้าง App5


  labPro[1] = "รายการสินค้า";
  labPrice[1] = "ราคา";
  labPro[5] = "รวมเป็นเงิน";

  labPro[1].align(ALIGN_TOP_LEFT, 5, 0);
  labPrice[1].align(labPro[1], ALIGN_RIGHT, 10, 0);
  labPro[2].align(labPro[1], ALIGN_BOTTOM, 0, 0);
  labPrice[2].align(labPrice[1], ALIGN_BOTTOM, 0, 0);
  labPro[3].align(labPro[2], ALIGN_BOTTOM, 0, 0);
  labPrice[3].align(labPrice[2], ALIGN_BOTTOM, 0, 0);
  labPro[4].align(labPro[3], ALIGN_BOTTOM, 0, 0);
  labPrice[4].align(labPrice[3], ALIGN_BOTTOM, 0, 0);
  labPro[5].align(labPro[4], ALIGN_BOTTOM, 0, 0);
  labPrice[5].align(labPrice[4], ALIGN_BOTTOM, 0, 0);

  A5btnPay.parent(App[5]);
  A5btnPay = "OK";
  A5btnPay.align(ALIGN_BOTTOM_RIGHT, 0, 0);



  A5btnPay.onClicked([](GWIDGET) {        //ถ้ากดปุ่ม ตั้งค่า
    close_App();
    Serial.println("จ่ายเงิน");
    IntCancel = 30;
    App[6].show(true);               //ให้แสดง myapp
  });
  // ----------------จบ App5

  // App6 QR code

  qrcode.parent(App[6]);
  BlynkGO.fillScreen(TFT_RED, TFT_ORANGE);

  qrcode.size(200, 200); // กำหนดขนาด กว้าง = ยาว ให้เท่ากัน
  qrcode.align(ALIGN_LEFT, 5, 0);
  // qrcode.version(17);    // กำหนด version ของ QR code  เพื่อรองรับ ความยาวสูงสุดที่จะรับได้ (ดูตารางด้านล่าง)
  qrcode.encode("กรุณาโอนเงิน " + String(intTotal) + " บาท");
  //  qrcode.encode("สวัสดีครับ", "SD://image/picture.png"); // หากต้องการใส่ logo ด้วย ควรมีขนาด 60x60pixels

  A6btn.parent(App[6]);
  A6btn = "ชำระ";
  A6btn.align(ALIGN_BOTTOM_RIGHT, 0, 0);



  // App7 ประกอบแฮมเบอเกอ
  ham[0] = img_ham1_1;
  ham[1] = img_ham5_1;
  ham[5] = img_ham1_2;


  for(int r = 0; r <= 8; r++) {
    ham[r].align(ALIGN_BOTTOM, 0, -20);
    ham[r].parent(App[7]);
    ham[r].show(0);
  }

  A6labPayTxt = "ยอดขายรวม  ";
  A6labPayTxt.align(ALIGN_TOP_LEFT, 5, 5);
  A6labPay.align(A6labPayTxt, ALIGN_RIGHT, 5, 0);



  A6btn.onClicked([](GWIDGET) {        //ถ้ากดปุ่ม ตั้งค่า
    close_App();
    intGTotal = intGTotal + intTotal; //เก็บยอดขาย ล้างยอด intGTotal= =0
    A6labPay = intGTotal;
    BlynkGO.flashMem("intGTotal", intGTotal);  //เก็บค่าลง flash memory
    Serial.println("ยืนยันการชำระเงิน");
    IntCancel = 30;
    timer.pause();
    //  timer.del();  //ปิด timer
    App[7].show(true);               //ให้แสดง myapp
    Run_App7();

  });
  BtnApp7 = "รับสินค้า";
  BtnApp7.align(ALIGN_TOP, 0, 40);
  BtnApp7.onClicked([](GWIDGET) {        //ถ้ากดปุ่ม ตั้งค่า
    close_App();
    Serial.println("บันทึกรายการสั่งซื้อ");
    IntCancel = 30;
    ProHam = 0;
    RApp1.show(true);
    A0labCancel.font(prasanmit_30, TFT_PIGBLOOD);
    A0labCancel.align(ALIGN_CENTER);
    A0labCancel = "กดหน้าจอ เพื่อสั่งสินค้า";


  });
  intGTotal = (int16_t) BlynkGO.flashMem_Int("intGTotal"); //ดึงค่าจาก flash memory
  A6labPay = intGTotal;
  CancelClicked();
  A0labCancel.toForeground();  // ลากไว้บนสุด ของ แม่เดียวกัน
  A6labPay.toForeground();
  close_App();
  App[2].show(true);
}

// ----------------------------------------------- จบ setup


void loop()
{
  BlynkGO.update();
}
