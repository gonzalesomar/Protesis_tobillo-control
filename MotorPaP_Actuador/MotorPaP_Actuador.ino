//CLOCKWISE: ROTACION INTERNA
// ANTICLOCKWISE: ROTACION EXTERNA

/*
 * ASIGNACION DE PINES AL ESP32
 */

// Motor PaP
#define IN1 25
#define IN2 26
#define IN3 27
#define IN4 14
#define HOME 13 //SW1 
#define HOME2 12 //SW2

const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };

int motorSpeed = 2000;   //variable para fijar la velocidad
int stepCounter = 0;     // contador para los pasos
int stepsPerRev = 4096;  // pasos para una vuelta completa


double angulo1 = 21; //limite de angulo de pie de rotacion interna
double angulo2 = 13; //limite de angulo de pie de rotacion externa

double StepsA1; //conversion de angulo 1 a steps del driver
double StepsA2; //conversion de angulo 2 a steps del driver
double regreso = 17*11.37;


int   Value;
int   Value2;

double angulo_giro[] = {17.61627, 17.45232, 17.05074, 16.43101, 15.61777, 14.63814, 13.51924, 12.28637, 10.96213, 9.56683, 8.11965, 6.64022, 5.1499, 3.67241, 2.23364, 0.86064, -0.42002, -1.58416, -2.61207, -3.49027, -4.21292, -4.78236, -5.2087, -5.50832, -5.70162, -5.81058, -5.85691, -5.8611, -5.84267, -5.82101, -5.81641, -5.85043, -5.94519, -6.12133, -6.3949, -6.77368, -7.25398, -7.8189, -8.43896, -9.07505, -9.68306, -10.21925, -10.64533, -10.93266, -11.06492, -11.03913, -10.8649, -10.56199, -10.15666, -9.6775, -9.15156, -8.60137, -8.04333, -7.48746, -6.93831, -6.39651, -5.86049, -5.32796, -4.79691, -4.26622, -3.73584, -3.2068, -2.68117, -2.16184, -1.65224, -1.15593, -0.6759, -0.21376, 0.23115, 0.66256, 1.0879, 1.51851, 1.96949, 2.4591, 3.00766, 3.63606, 4.36377, 5.20652, 6.17384, 7.26659, 8.47486, 9.77658, 11.13728, 12.51116, 13.84376, 15.07613, 16.15001, 17.01332, 17.62523, 17.95991, 18.00873, 17.78058, 17.30038, 16.60591};
double steps_giro[] ={200.2969899, 198.4328784, 193.8669138, 186.8205837, 177.5740449, 166.4356518, 153.7137588, 139.6960269, 124.63941809999999, 108.77485709999999, 92.3204205, 75.4993014, 58.554362999999995, 41.7553017, 25.396486799999998, 9.7854768, -4.775627399999999, -18.0118992, -29.699235899999998, -39.6843699, -47.900900400000005, -54.375433199999996, -59.222919, -62.6295984, -64.8274194, -66.06629459999999, -66.5930667, -66.640707, -66.4311579, -66.1848837, -66.1325817, -66.5193891, -67.5968103, -69.5995221, -72.71001299999999, -77.01674159999999, -82.4777526, -88.900893, -95.95097519999999, -103.18331849999998, -110.09639219999998, -116.1928725, -121.03740209999998, -124.30434419999999, -125.8081404, -125.5149081, -123.533913, -120.08982629999998, -115.4812242, -110.033175, -104.0532372, -97.79757689999998, -91.45266209999998, -85.13242019999998, -78.8885847, -72.7283187, -66.6337713, -60.578905199999994, -54.54086669999999, -48.506921399999996, -42.4765008, -36.461316, -30.484902899999994, -24.5801208, -18.7859688, -13.142924099999998, -7.684982999999999, -2.4304512, 2.6281754999999998, 7.5333072, 12.369423, 17.2654587, 22.393101299999998, 27.959966999999995, 34.197094199999995, 41.342002199999996, 49.61606489999999, 59.1981324, 70.1965608, 82.6211283, 96.3591582, 111.15971459999999, 126.6308736, 142.2518892, 157.40355119999998, 171.41559809999998, 183.6256137, 193.44144839999998, 200.39886509999997, 204.2041767, 204.75926009999998, 202.16519459999998, 196.7053206, 188.8091967};
double variaciones[] = {200.2969899, -1.864111500000007, -4.565964600000001, -7.046330100000006, -9.246538799999996, -11.138393100000002, -12.721892999999994, -14.017731900000001, -15.056608800000006, -15.864560999999995, -16.454436599999994, -16.821119100000004, -16.944938399999998, -16.799061299999998, -16.3588149, -15.611009999999998, -14.561104199999999, -13.236271799999999, -11.6873367, -9.985134000000002, -8.216530500000005, -6.4745327999999915, -4.847485800000001, -3.4066794000000016, -2.1978209999999976, -1.2388751999999954, -0.5267721000000023, -0.04764030000001185, 0.20954910000000382, 0.246274200000002, 0.052301999999997406, -0.386807399999995, -1.0774212000000034, -2.0027118, -3.110490899999988, -4.3067286, -5.461011000000013, -6.423140399999994, -7.050082199999991, -7.232343299999997, -6.913073699999998, -6.09648030000001, -4.844529599999987, -3.2669421000000085, -1.5037962000000107, 0.29323229999999967, 1.9809951000000012, 3.444086700000014, 4.608602099999985, 5.4480492, 5.979937800000002, 6.255660300000017, 6.344914799999998, 6.320241899999999, 6.243835499999989, 6.160265999999993, 6.094547399999996, 6.054866100000012, 6.038038500000006, 6.033945299999992, 6.030420599999999, 6.0151848, 5.976413100000002, 5.904782099999995, 5.794152, 5.643044700000001, 5.457941099999999, 5.254531799999999, 5.0586267, 4.9051317, 4.836115799999999, 4.8960357000000005, 5.127642599999998, 5.5668656999999975, 6.2371272, 7.144908000000001, 8.274062699999995, 9.582067500000008, 10.998428400000002, 12.424567499999995, 13.7380299, 14.80055639999999, 15.471159000000014, 15.621015599999993, 15.151661999999988, 14.012046900000001, 12.21001560000002, 9.815834699999982, 6.957416699999982, 3.8053116000000387, 0.5550833999999725, -2.5940654999999992, -5.459873999999985, -7.896123899999992};
int motor_size = sizeof(variaciones)/sizeof(variaciones[1]);

double pasos;
int p = 0;

// Actuadores Lineales
const int Extend_pinA1 = 4; // IN3
const int Retract_pinA1 = 15; // IN4
const int Position_pinA1 = 34; // feedback position del actuador
int RC_locationA1=0;
int actual_locationA1=0;

const int Extend_pinA2 = 17; //Tx2 - in1
const int Retract_pinA2 = 16; //rx2 -in2
const int Position_pinA2 = 39; // feedback position del actuador
int RC_locationA2=0;
int actual_locationA2=0;
int deadbandA1 = 60;
int deadbandA2 = 30;
int senal=0;

double LongitudA1=0;
double LongitudA2=0;

int tablaA1[] = {9, 10, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 32, 33, 34, 35, 35, 35, 35, 35, 35, 35, 34, 34, 33, 32, 32, 31, 31, 30, 30, 30, 29, 29, 29, 29, 29, 29, 29, 30, 30, 31, 32, 33, 34, 35, 36, 37, 37, 38, 39, 39, 40, 40, 40, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 40, 40, 39, 39, 38, 36, 35, 33, 31, 29, 27, 24, 21, 19, 16, 13, 11, 10, 8, 7, 7, 7, 8,13};
int tablaA2[] = {9, 10, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 32, 33, 34, 35, 35, 35, 35, 35, 35, 35, 34, 34, 33, 32, 32, 31, 31, 30, 30, 30, 29, 29, 29, 29, 29, 29, 29, 30, 30, 31, 32, 33, 34, 35, 36, 37, 37, 38, 39, 39, 40, 40, 40, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 40, 40, 39, 39, 38, 36, 35, 33, 31, 29, 27, 24, 21, 19, 16, 13, 11, 10, 8, 7, 7, 7, 8,13};

int arr_sizeA1 = sizeof(tablaA1)/sizeof(tablaA1[1]);
int arr_sizeA2 = sizeof(tablaA2)/sizeof(tablaA2[1]);

int flagA1 = 1;
int flagA2 = 1;
int i = 0;
int j = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(HOME, INPUT_PULLUP);
  pinMode(HOME2, INPUT_PULLUP);

  pinMode(Extend_pinA1, OUTPUT);
  pinMode(Retract_pinA1, OUTPUT);
  pinMode(Extend_pinA2, OUTPUT);
  pinMode(Retract_pinA2, OUTPUT);
  digitalWrite(Extend_pinA1, LOW);
  digitalWrite(Retract_pinA1, LOW);
  digitalWrite(Extend_pinA2, LOW);
  digitalWrite(Retract_pinA2, LOW);

  while(1){
    Value = digitalRead(HOME);
    Value2 = digitalRead(HOME2);
    anticlockwise();
    delayMicroseconds(motorSpeed);
    
    if(Value2 == 1){
      for (int i = 0; i < regreso; i++){
        clockwise();
        delayMicroseconds(motorSpeed);
      }
      break;
    }
  }
}

void loop() {
  if(flagA1 && i<arr_sizeA1){
    LongitudA1 = tablaA1[i];
    flagA1 = 0;
    i++;
  }
  if(flagA2 && j<arr_sizeA2){
    LongitudA2 = tablaA2[j];
    flagA2 = 0;
    j++;
  }
  
  if ((LongitudA1 >= 0) && (LongitudA1 <= 4)){
    RC_locationA1 = 0;
  }
  if ((LongitudA2 >= 0) && (LongitudA2 <= 4)){
    RC_locationA2 = 0;
  }

  if ((LongitudA1 > 4) && (LongitudA1 < 47)){
    RC_locationA1 = 95.233 * LongitudA1 - 380.93;
  }
  if ((LongitudA2 > 4) && (LongitudA2 < 47)){
    RC_locationA2 = 95.233 * LongitudA2 - 380.93;
  }

  if ((LongitudA1 >= 47)){
    RC_locationA1 = 4095;
  }
  if ((LongitudA2 >= 47)){
    RC_locationA2 = 4095;
  }

  actual_locationA1 = analogRead(Position_pinA1);
  actual_locationA2 = analogRead(Position_pinA2);


 /* Serial.print(actual_locationA1);
  Serial.print("----");
  Serial.print(RC_locationA1);
  Serial.print("----");
  Serial.print(i);
  Serial.print("----");
  Serial.println(LongitudA1);*/

// Actuador 1
  if ((actual_locationA1 <= RC_locationA1 + deadbandA1) && (actual_locationA1 >= RC_locationA1 - deadbandA1)){
    digitalWrite(Extend_pinA1, LOW);
    digitalWrite(Retract_pinA1, LOW);
    flagA1 = 1;
  }

// Actuador 2
  if ((actual_locationA2 <= RC_locationA2 + deadbandA2) && (actual_locationA2 >= RC_locationA2 - deadbandA2)){
    digitalWrite(Extend_pinA2, LOW);
    digitalWrite(Retract_pinA2, LOW);
    flagA2 = 1;
  }

  if((actual_locationA1 > RC_locationA1 + deadbandA1) && (flagA1 == 0)){
    digitalWrite(Extend_pinA1, HIGH);
    digitalWrite(Retract_pinA1, LOW);
  }

  if((actual_locationA2 > RC_locationA2 + deadbandA2) && (flagA2 == 0)){
    digitalWrite(Extend_pinA2, HIGH);
    digitalWrite(Retract_pinA2, LOW);
  }

  if((actual_locationA1 < RC_locationA1 - deadbandA1) && (flagA1 == 0)){
    digitalWrite(Extend_pinA1, LOW);
    digitalWrite(Retract_pinA1, HIGH);
  }

  if((actual_locationA2 < RC_locationA2 - deadbandA2) && (flagA2 == 0)){
    digitalWrite(Extend_pinA2, LOW);
    digitalWrite(Retract_pinA2, HIGH);
  }

 // Motor Paso a Paso
  if(p<motor_size){
    pasos = variaciones[p];
    if (pasos >= 0){
      //ROTACION INTERNA
      for (int i = 0; i < pasos; i++){
         anticlockwise();
         delayMicroseconds(motorSpeed);
        }
    }
    else{
      //ROTACION EXTERNA
      pasos = pasos*-1;
      for (int i = 0; i < pasos; i++){
          clockwise();
          delayMicroseconds(motorSpeed);
      }
    } 
    p++;
  }  
}

void clockwise()
{
  stepCounter++;
  if (stepCounter >= numSteps) stepCounter = 0;
  setOutput(stepCounter);
}
void anticlockwise()
{
  stepCounter--;
  if (stepCounter < 0) stepCounter = numSteps - 1;
  setOutput(stepCounter);
}
void setOutput(int step)
{
  digitalWrite(IN1, bitRead(stepsLookup[step], 0));
  digitalWrite(IN2, bitRead(stepsLookup[step], 1));
  digitalWrite(IN3, bitRead(stepsLookup[step], 2));
  digitalWrite(IN4, bitRead(stepsLookup[step], 3));
}

