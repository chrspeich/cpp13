#include "profiler.hpp"
#include <iostream>

namespace Prof {

	const double CLOCK_TICKTIME = std::chrono::high_resolution_clock::period::num/double(std::chrono::high_resolution_clock::period::den);


	// ********************************************************************* //
	// ProfileStack
	// ********************************************************************* //

	void ProfileStack::push()
	{
		m_TimeStack.push(0);
	}

	Ticks ProfileStack::pop( const Ticks& functionTime )
	{
		Ticks t = m_TimeStack.top();
		m_TimeStack.pop();

		// Now add the time we used to the parents time
		if (!m_TimeStack.empty()) {
			Ticks t_parent = m_TimeStack.top();
			t_parent += functionTime;
			m_TimeStack.pop();
			m_TimeStack.push(t_parent);
		}

		return t;
	}


	
	// ********************************************************************* //
	// ProfileCollector
	// ********************************************************************* //
	ProfileCollector::~ProfileCollector()
	{
		std::chrono::high_resolution_clock::now();
		std::cerr << "Consumed time in    " << m_function << "()   [" << m_file << "] :\n    ";
		std::cerr << (m_collectetedTime*CLOCK_TICKTIME*1000.0) << " ms    [";
		std::cerr << (m_collectetedTimeExclusive*CLOCK_TICKTIME*1000.0) << " ms]\n";
	}



	// ********************************************************************* //
	// ScopeProfiler
	// ********************************************************************* //
	ScopeProfiler::ScopeProfiler( ProfileCollector& collector ) :
			m_collector( collector )
	{
		m_startPoint = std::chrono::high_resolution_clock::now();
		ProfileStack::getSharedInstance().push();
	}

	ScopeProfiler::~ScopeProfiler()
	{
		Ticks timeSpan = (std::chrono::high_resolution_clock::now()-m_startPoint).count();
		// TODO: Use ProfilerStack
		Ticks subTime = ProfileStack::getSharedInstance().pop(timeSpan);
		m_collector.addTime( timeSpan, timeSpan-subTime );
	}

};