#pragma once

#include <chrono>
#include <stack>

namespace Prof {
	
	typedef std::chrono::high_resolution_clock::rep Ticks;


	class ProfileStack
	{
	public:
		/// \brief Starts a new counting by creating a zero-entry on the stack.
		///
		void push();
		
		/// \brief Gives the time occupied by profiled subfunctions and takes
		///		a number for the upper level caller function.
		/// \param functionTime [in] The total value of the time scince the
		///		according push command.
		/// \return The time which was occupied by profiled subfunctions inside the
		///		current scope.
		Ticks pop( const Ticks& functionTime );

		/// \brief Singleton access.
		static ProfileStack& getSharedInstance()
		{
			static ProfileStack* stack = nullptr;

			if (stack == nullptr) {
				stack = new ProfileStack();
			}

			return *stack;
		}

	private:
		std::stack<Ticks> m_TimeStack;

		ProfileStack() : m_TimeStack() {};
		ProfileStack( const ProfileStack& ) = delete;
	};



	/// \brief An object which creates an output of all collected times
	///		on destruction.
	/// \details The intend is that instances of this class are used as static
	///		variables which collect all times during the whole program runtime.
	///
	///		Drawbacks of this profiler:
	///		* It measures "Wall time" which means an interruption of a function
	///			is recognized as funtion time as well.
	///		* The code must be changed by the PROFILE macro.
	class ProfileCollector
	{
	public:
		ProfileCollector( const char* file, const char* function ) :
			m_collectetedTime( 0 ),
			m_collectetedTimeExclusive( 0 ),
			m_file( file ),
			m_function( function )
		{}

		/// \brief Destructor which outputs result to std::cerr.
		///
		~ProfileCollector();

		/// \brief Sum the measured time over the whole program runtime.
		/// \param inclusive [in] The total time passed in the current scope.
		/// \param exclusive [in] The time passed in the current scope without
		///		the time measured in subfunctions.
		void addTime( const Ticks& inclusive, const Ticks& exclusive )
		{
			m_collectetedTime += inclusive;
			m_collectetedTimeExclusive += exclusive;
		}

	private:
		Ticks m_collectetedTime;
		Ticks m_collectetedTimeExclusive;

		// Initial information which function is profiled.
		const char* m_file;			///< Source file name of the function
		const char* m_function;		///< The name of the profiled function
	};


	/// \brief A class which measures the time between construction and
	///		destruction.
	/// \details The results are given to a collector instance.
	class ScopeProfiler
	{
	public:
		ScopeProfiler( ProfileCollector& collector );

		~ScopeProfiler();

	private:
		std::chrono::high_resolution_clock::time_point m_startPoint;
		ProfileCollector& m_collector;
	};

	/// \brief This makro enables profiling for the scope in which it is used.
	///
#define PROFILE	static Prof::ProfileCollector localCollector( __FILE__, __FUNCTION__ );\
				Prof::ScopeProfiler localTimer( localCollector );

};