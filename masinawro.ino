int _output_PD5 = 5;
int _output_PD4 = 4;
int _output_PD7 = 7;
int _output_PD6 = 6;
int _output_PWM10 = 10;
int _output_PWM9 = 9;
int _led_L = 13;

void setup() {
    pinMode(_output_PD5, OUTPUT);
    pinMode(_output_PD4, OUTPUT);
    pinMode(_output_PD7, OUTPUT);
    pinMode(_output_PD6, OUTPUT);
    pinMode(_output_PWM10, OUTPUT);
    pinMode(_output_PWM9, OUTPUT);
    pinMode(_led_L, OUTPUT);
}

void inainte() {
    digitalWrite(_output_PD4, LOW);  // Motorul 1 înainte
    digitalWrite(_output_PD5, HIGH);
    digitalWrite(_output_PD6, LOW);  // Motorul 2 înainte
    digitalWrite(_output_PD7, HIGH);
    analogWrite(_output_PWM9, 100);  // Viteză motor
    analogWrite(_output_PWM10, 100);
}

void stanga() {
    digitalWrite(_output_PD4, LOW);   // Motorul 1 oprire
    digitalWrite(_output_PD5, LOW);
    digitalWrite(_output_PD6, LOW);   // Motorul 2 înainte
    digitalWrite(_output_PD7, HIGH);
    analogWrite(_output_PWM9, 100);   // Viteză motor
    analogWrite(_output_PWM10, 100);
    delay(500);  // Țineți-l stânga pentru 0.5 secunde
}

void dreapta() {
    digitalWrite(_output_PD4, LOW);   // Motorul 1 înainte
    digitalWrite(_output_PD5, HIGH);
    digitalWrite(_output_PD6, LOW);   // Motorul 2 oprire
    digitalWrite(_output_PD7, LOW);
    analogWrite(_output_PWM9, 100);   // Viteză motor
    analogWrite(_output_PWM10, 100);
    delay(500);  // Țineți-l dreapta pentru 0.5 secunde
}

void inapoi() {
    digitalWrite(_output_PD4, HIGH);  // Motorul 1 înapoi
    digitalWrite(_output_PD5, LOW);
    digitalWrite(_output_PD6, HIGH);  // Motorul 2 înapoi
    digitalWrite(_output_PD7, LOW);
    analogWrite(_output_PWM9, 100);  // Viteză motor
    analogWrite(_output_PWM10, 100);
    delay(1000);  // Mergi înapoi pentru 1 secundă
}

void stop() {
    digitalWrite(_output_PD4, LOW);   // Oprește motorul 1
    digitalWrite(_output_PD5, LOW);
    digitalWrite(_output_PD6, LOW);   // Oprește motorul 2
    digitalWrite(_output_PD7, LOW);
    analogWrite(_output_PWM9, 0);     // Oprește ambele motoare
    analogWrite(_output_PWM10, 0);
    delay(500);  // Așteaptă o scurtă pauză
}

void loop() {
    inainte();   // Mergi înainte
    delay(2000); // Așteaptă 1 secundă
    stanga(); 
    // Virează la stânga
    stop();      // Oprește-te
    inainte();   // Mergi înainte
    delay(2000); // Așteaptă 1 secundă
    dreapta();   // Virează la dreapta
    stop();      // Oprește-te
    inapoi();
    delay(2000);// Mergi înapoi
    stop();      // Oprește-te
}
