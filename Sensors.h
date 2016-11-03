template <typename T> class Sensor {
  protected:
    int pin;
    T _value;
    virtual void refresh (void);
    virtual void pinMode_hook (void);
  public:
    Sensor (int input) { pin = input; };
    T read() { refresh(); return cachedRead(); }
    T cachedRead(void) const { return _value; }
};

class AnalogSensor : public Sensor<int> {
  private:
    void refresh (void) { _value = analogRead(pin); };
    void pinMode_hook (void) { pinMode(pin, INPUT); }
  public:
    AnalogSensor (int input) : Sensor(input) { pin = input; };
};

// T è il tipo di dato dello stato
// O è il tipo di dato dell'uscita
// S è la classe del sensore
template <typename T, typename O, class S> class Controller {
  protected:
    S sensor;
    T target;
  public:
    Controller (S input) : sensor(input) {};
    void setTarget(T input) { target = input; }
    virtual O update();
};

// T è il tipo di dato dello stato
// S è la classe del sensore
template <typename T, class S> class OnOffController : Controller<T, bool, S> {
  using Controller<T, bool, S>::sensor;
  protected:
    T thresholdHi, thresholdLo;
    bool output = false;
  public:
    OnOffController(S input) : Controller<T, bool, S>(input) { };
    OnOffController(S input, T _thresholdHi, T _thresholdLo) : Controller<T, bool, S>(input) {
      thresholdHi = _thresholdHi;
      thresholdLo = _thresholdLo;
    };
    
    void setThreshold(T hi, T lo) {
      thresholdHi = hi;
      thresholdLo = lo;
    }
    bool update() {
      sensor.read();
      if (output == false && sensor.cachedRead() > thresholdHi) {
        output = true;
      } else if (output == true && sensor.cachedRead() < thresholdLo) {
        output = false;
      }
      return output;
    }
};
