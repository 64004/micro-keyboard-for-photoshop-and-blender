#include <Keyboard.h>

#define CLK 8
#define DT 9
#define SW 4

int lastStateCLK;

void setup() {
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
  
  Keyboard.begin();
  // Считываем начальное состояние
  lastStateCLK = digitalRead(CLK);
}

void loop() {
  int currentStateCLK = digitalRead(CLK);

  // Если состояние CLK изменилось — значит, было вращение
  if (currentStateCLK != lastStateCLK && currentStateCLK == LOW) {
    // Проверяем направление, сравнивая CLK и DT
    if (digitalRead(DT) != currentStateCLK) {
      // По часовой -> Приближаем (Ctrl + "=")
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('=');
    } else {
      // Против часовой -> Отдаляем (Ctrl + "-")
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('-');
    }
    delay(25); // Короткая пауза, чтобы компьютер успел обработать нажатие
    Keyboard.releaseAll();
  }
  
  lastStateCLK = currentStateCLK;

  // Логика кнопки (Ctrl + Z)
  if (digitalRead(SW) == LOW) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('z');
    delay(50);
    Keyboard.releaseAll();
    delay(300); // Защита от повторных срабатываний
  }
}
