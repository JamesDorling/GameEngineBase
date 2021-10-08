/*! \file bufferLayout.h  */
#pragma once

#include "shaderDataType.h"
#include <vector>
namespace Engine 
{
	/**
	* \class VertexBufferElement
	* /brief A class that holds a single element of data in a vertex buffer layout.
	*/
	class VertexBufferElement
	{
	public:
		ShaderDataType m_dataType; //!< Which shader data type is it?
		uint32_t m_size; //!< Size of the shader data type assigned
		uint32_t m_offset; //!< Offset
		bool m_normalised; //!< Is it normalised?

		VertexBufferElement() {}; //!< Default constructor
		VertexBufferElement(ShaderDataType dataType, bool normalised = false) : m_dataType(dataType), m_size(SDT::size(dataType)), m_offset(0), m_normalised(normalised) {} //!< Constructor with parameters
	};

	/**
	* \class UniformBufferElement
	* /brief A class that holds a single data element in a uniform buffer layout.
	*/
	class UniformBufferElement
	{
	public:
		const char * m_name;
		ShaderDataType m_dataType; //!< Which shader data type is it?
		uint32_t m_size; //!< Size of the shader data type assigned
		uint32_t m_offset; //!< Offset
		bool m_normalised; //!< Is it normalised?

		UniformBufferElement() {}; //!< Default constructor
		UniformBufferElement(const char * name, ShaderDataType dataType) : 
			m_name(name), 
			m_dataType(dataType), 
			m_size(SDT::std140align(dataType)), 
			m_offset(0) {} //!< Constructor with parameters (Name, datatype)
	};

	/**
	* \class BufferLayout
	* /brief An abstraction of the notion of the buffer layout
	*/
	template  <class G>
	class BufferLayout
	{
	public:
		BufferLayout<G>() {}; //!< Default Constructor
		BufferLayout<G>(const std::initializer_list<G>& element, uint32_t stride = 0) : m_elements(element), m_stride(stride) { calcStrideAndOffset(); }
		inline uint32_t getStride() const { return m_stride; } //!< Getter for the stride
		void addElement(G element); //!< Add an element to hte buffer layout
		inline typename std::vector<G>::iterator begin() { return m_elements.begin(); }				//!< Starts the BufferLayout using an iterator
		inline typename std::vector<G>::iterator end() { return m_elements.end(); }					//!< Ends the bufferLayout using an iterator
		inline typename std::vector<G>::const_iterator begin() const { return m_elements.begin(); } //!< Starts the BufferLayout using a const iterator
		inline typename std::vector<G>::const_iterator end() const { return m_elements.end(); }		//!< Ends the bufferLayout using a const iterator
	private:
		std::vector<G> m_elements; //!< Buffer Elements
		uint32_t m_stride; //!< Width of the buffer line in bytes
		void calcStrideAndOffset(); //!< Use the elements to calculate the stride and the offset
	};

	template  <class G>
	void BufferLayout<G>::addElement(G element)
	{
		m_elements.push_back(element);
		calcStrideAndOffset();
	}

	template  <class G>
	void BufferLayout<G>::calcStrideAndOffset()
	{

		uint32_t l_offset = 0;

		for (auto& element : m_elements)
		{
			element.m_offset = l_offset;
			l_offset += element.m_size;
		}

		if (m_stride == 0) m_stride = l_offset;

	}

	using VertexBufferLayout  = BufferLayout<VertexBufferElement>;	//!< template to use BufferLayout when VertexBufferLayout is passed
	using UniformBufferLayout = BufferLayout<UniformBufferElement>; //!< template to use BufferLayout when UniformBufferLayout is passed

}