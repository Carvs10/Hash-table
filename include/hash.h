#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <memory>
#include <iterator>
#include <string>
#include <vector>
#include <forward_list>
#include <initializer_list>//std::initializer_list
#include <math.h>

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
            class HashEntry {//! Hash entry class

                  public:

                        HashEntry ( KeyType k_, DataType d_ ) : m_key( k_ ), m_data( d_ )
                        {/*Empty*/};

                        KeyType m_key;   //!< Stores the key for an entry.
                        DataType m_data; //!< Stores the data for an entry.

            }

            using Entry = HashEntry < KeyType, DataType >; //! Alias

            //!<Contructors and destructor

            HashTbl ( size_t tbl_size = DEFAULT_SIZE ): m_size { tbl_size }, m_count { 0 }
            {
                  m_data_table.resize( DEFAULT_SIZE );
            }

            virtual ~HashTbl ();

            HashTbl ( const Hashtbl& ); //Hashtbl??

            HashTbl ( std::initializer_list < Entry > ilist );

            HashTbl& operator= ( const Hashtbl & );

            HashTbl& operator= ( std::initializer_list < Entry > ilist );

            bool insert ( const KeyType & k_, const DataType & d_ );

            bool erase ( const KeyType & k_ );

            bool retrieve ( const KeyType & k_, DataType & d_ ) const;

            void clear ( void );

            bool empty ( void ) const;

            size_t size ( void ) const;

            DataType& at( const KeyType& k_ );

            DataType& operator[] ( const KeyType& k_ );

            size_t count ( const KeyType& k_ ) const;

            friend std::ostream& operator<< ( std::ostream &, const HashTbl& );//stdostream

      private:

            void rehash();                      //! Change Hash table if load factor λ > 1.

            unsigned int m_size;          //! Hash table size.

            unsigned int m_count;         //! Number of elements currently stored in the table.

            //!< The table: array of pointers to collision list.
            std::forward_list< Entry > * m_data_table
            //std::unique_ptr < std::forward_list< Entry > [] > m_data_table
            
            static const short DEFAULT_SIZE = 11;//! Hash table’s default size: 11 table entries.

}

#endif