void grabar(int addr, String a) {
  int tamano = a.length();
  char inchar[50];
  a.toCharArray(inchar, tamano + 1);
  for (int i = 0; i < tamano; i++) {
    EEPROM.write(addr + i, inchar[i]);
  }
  for (int i = tamano; i < 50; i++) {
    EEPROM.write(addr + i, 255);
  }
  EEPROM.commit();
}

String leer(int addr) {
  byte lectura;
  String strlectura;
  for (int i = addr; i < addr + 50; i++) {
    lectura = EEPROM.read(i);
    if (lectura != 255) {
      strlectura += (char)lectura;
    }
  }
  return strlectura;
}

String GetBodyContent(uint8_t *data, size_t len)
{
  String content = "";
  for (size_t i = 0; i < len; i++) {
    content .concat((char)data[i]);
  }
  return content;
}

void resetESP() {
  for (int i = 0; i < 512; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.end();
  delay(5000);
  ESP.reset();
}
