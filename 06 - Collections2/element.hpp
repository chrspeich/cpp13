#pragma once

namespace Collections
{

	/**
	 * Abstract base class to handle arbitrary types to be collected.
	 *
	 * For each different dataset you would like to store inherite from this
	 * interface class. It is even possible to store differend kinds of
	 * elements into one container.
	 */
	class IElement
	{
	public:
		/// \brief Implementation of a destructor to remove everything
		///		referenced by this element.
		virtual ~IElement() {}

		/// \brief Create a copy of this element on the heap (new).
		///
		virtual IElement* clone() const = 0;
	};

};