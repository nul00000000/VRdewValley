class Power {
public:
	Power(double level, double capacity);

	void update(double t);
	void set_charge_rate(double charge_rate);
	void set_discharge_rate(double discharge_rate);

	double m_level;
	double m_capacity;

	double charge_rate;
	double discharge_rate;

private:
	double prev_t;
};
