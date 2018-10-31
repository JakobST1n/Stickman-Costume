#define OUTPIN 1
#define DIMPIN 3

int CBrightness = 0;
int CDimDirection = 1;

void setup() {
  pinMode(OUTPIN, OUTPUT);
  pinMode(DIMPIN, INPUT);
}

void loop() {
  delay(1);
 
 if (digitalRead(DIMPIN) == HIGH) { dim(); }
 analogWrite(OUTPIN, CBrightness); 
}

void dim() {
  if (CDimDirection == 1) {
    CBrightness++;
  }
  if (CDimDirection == 0) {
    CBrightness--;
  }
  if (CBrightness >= 255) {
    CDimDirection = 0;
  }
  if (CBrightness <= 0) {
    CDimDirection = 1;
  }
}
