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



        HashTbl( size_t tbl_size = DEFAULT_SIZE );

            virtual ~Hashtbl ();

            HashTbl (const Hashtbl &);

            HashTbl ( std::initializer_list<Entry> ilist );

            HashTbl& operator= ( const HashTbl &);

            HashTbl& operator= ( std::initializer_list<Entry> ilist );

            bool insert ( const KeyType & k_, const DataType & d_ );

            bool erase( const KeyType & k_ );

            bool retrive ( const KeyType & k_, DataType & d_ ) const;

            bool clear ( void );

            bool empty( void ) const;

            size_t size( void ) const ;

            DataType& at( const KeyType& k_ );

            DataType& operator[]( const KeyType& k_);

            size_t count( const KeyType& k_ ) const;




            private:

            void rehash(); //!< Change Hash table size if load factor.

            unsigned int m_size; //!< Hash Table size
            unsigned int m_count; //!< Number of elements currently stored in the table

            //!< The table: array of pointers to collision list
            std::forward_list< Entry > * m_data_type;

            //! Hash table's default size: 11 table entries
            static const short DEFAULT_SIZE = 11;



}

#endif