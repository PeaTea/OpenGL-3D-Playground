#include "Timer.h"
#include "OutUtils.h"

using std::chrono::milliseconds;

RAIITimer::RAIITimer(conststrref name)
    :   m_name  {name}
{
    m_start = hr_clock::now();
}

RAIITimer::~RAIITimer()
{
    m_end = hr_clock::now();
    uint duration = std::chrono::duration_cast<milliseconds>(m_end - m_start).count();
    logging::log(m_name + " finished in " + std::to_string(duration) + "ms");
}