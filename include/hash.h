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


                        bool Prime(int number){
                            
                            for(int i=2; i < number; i++){
                                if(number % i == 0){
                                    return false;
                                }
                            }
                            return true;
                        }

            }

            using Entry = HashEntry < KeyType, DataType >; //! Alias

            //!<Contructors and destructor

            HashTbl ( void ): m_size { DEFAULT_SIZE }, m_count { 0 }
            {
                  m_data_table.resize( DEFAULT_SIZE );
            }

            HashTbl ( size_t tbl_size ): m_size { next_prime( tbl_size ) }, m_count { 0 }
            {
                  m_data_table.resize( next_prime( tbl_size ) );
            }

            virtual ~HashTbl (){
                delete [] m_data_table;
            }

            HashTbl ( const Hashtbl& ): 

            HashTbl ( std::initializer_list < Entry > ilist );

            HashTbl& operator= ( const Hashtbl & );

            HashTbl& operator= ( std::initializer_list < Entry > ilist );

            bool insert ( const KeyType & k_, const DataType & d_ );

            bool erase ( const KeyType & k_ );

            bool retrieve ( const KeyType & k_, DataType & d_ ) const;

            /*!
             * Clear all the memory associated with collision lists from the table.
             * remove its elements
             */

            void clear ( void ){

                for(auto i(0u); i < m_size; i++){
                    m_data_table[i].clear();
                }

                m_count =0;
                m_size = 0;
            }

            /*!
              @return True if the hash is empty, or false otherwhise
              */

            bool empty ( void ) const{
                return m_count == 0;
            }

            /*! 
              @return the amount element sored ind the table.
             */

            size_t size ( void ) const{
                size_t size = 0;
                for(auto i(0u); i < m_size; i++){
                    for(auto it(m_data_table[i].begin(); it != m_data_table[i].end(); it++){
                        it++;
                    }
                }

                return size;
            }

            DataType& at( const KeyType& k_ );

            DataType& operator[] ( const KeyType& k_ );

            /*
             @return the amount of elements that are in collision list associated with key k_
             */

            size_t count ( const KeyType& k_ ) const{
                KeyHash hashFunc;

                auto end(hashFunc(k_) % m_size);
                size_t count = 0;
                for(auto it(m_data_table[i].begin(); it != m_data_table[i].end(); it++)){
                    count++;
                }

                return count;
            }

            friend std::ostream& operator<< ( std::ostream &, const HashTbl& );//stdostream

    //=== Private data.
      private:

            /*! 
             *Change Hash table if load factor λ > 1.
             */

            void rehash(){
                KeyHash hashFunc; // "Functor" for primary hash.

                unsigned int m_aux_size;

                for(auto i(m_size*2); i > 0; i++){
                    if(Prime(i)){
                        m_aux_size = i;
                        break;
                    }
                }

                std::foward_list< Entry > *m_data_table_aux = new std::foward_list <Entry>[m_aux_size];

                for(auto i(0u); i < m_size; i++){
                    auto it(m_data_table[i].begin());
                    while(it != m_data_table[i].end()){
                        auto end(hashFunc(it->m_key) % m_aux_size);
                        Entry new_entry(it->m_key, it->m_data);
                        m_data_table[end].push_front(new_entry);
                        it++;
                    }
                }

                m_size = m_aux_size;
                delete [] m_data_table;
                m_data_table = m_data_table_aux;
            }                      

            unsigned int m_size;          //! Hash table size.

            unsigned int m_count;         //! Number of elements currently stored in the table.

            //!< The table: array of pointers to collision list.
            std::forward_list< Entry > * m_data_table
            //std::unique_ptr < std::forward_list< Entry > [] > m_data_table
            
            static const short DEFAULT_SIZE = 11;//! Hash table’s default size: 11 table entries.

}

#endif