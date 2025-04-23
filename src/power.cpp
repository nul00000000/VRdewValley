#include "power.h"
// Power!

Power::Power(double level, double capacity) {
	m_level = level;
	m_capacity = capacity;

	prev_t = 0;
	charge_rate = 0;
	discharge_rate = 0;
}

void Power::update(double t) {
	double dt = t-prev_t;
	prev_t = t;
	m_level += (charge_rate-discharge_rate)*dt;

	if (m_level > 1) { m_level = 1; }
	if (m_level < 0) { m_level = 0; }
}
