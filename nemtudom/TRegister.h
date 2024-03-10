#ifndef TREGSITER_H
#define TREGSITER_H

#include <cstdint>
#include "ResourceManager.h"

namespace ex 
{
	class TRegister
	{
		public:
			TRegister() = default;
			~TRegister(); // Just defined doesnt require cleanup

			const uint32_t  getRegisterValue() const
			{  return m_registerValue;  }

			const size_t  getRegisterStartIndex() const
			{  return m_memoryStart;  }

			const size_t  getCurrentIndex() const
			{  return m_currentIndex;  }

			void  setRegisterStartIndex(size_t value)
			{  m_memoryStart = value; m_currentIndex = 0;  }

			void  setRegisterIndex(const size_t index)
			{  m_currentIndex = index;  }

			void  setRegisterValue(const uint32_t value)
			{  m_registerValue = value;  }

		private:
			size_t  m_memoryStart; // Variables name
			size_t  m_currentIndex;
			uint32_t  m_registerValue;
			ex::ResourceManager  m_resourceManager;
	};
}
#endif // ! TREGSITER_H