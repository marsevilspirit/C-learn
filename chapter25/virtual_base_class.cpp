class PoweredDevuce
{
};

class Scanner:virtual public PoweredDevuce
{
};

class Printer:virtual public PoweredDevuce
{
};

class Copier:public Scanner, public Printer
{
};
