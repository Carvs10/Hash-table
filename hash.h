#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <forward_list>

template 
< 
typename KeyType,
typename DataType,
typename KeyHash = std::hash < KeyType > ,
typename KeyEqual = std::equal_to < KeyType >
>
class HashTbl {

	public:

		template < class KeyType, class DataType >
		class HashEntry {

			public:

				HashEntry ( KeyType k_, DataType d_ ) : m_key( k_ ), m_data( d_ )
				{/*Empty*/};

				KeyType m_key;   //!< Stores the key for an entry.
				DataType m_data; //!< Stores the data for an entry.

		}

		using Entry = HashEntry < KeyType, DataType >; //! Alias

}

#endif