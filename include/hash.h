#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <memory>
#include <iterator>
#include <string>
#include <vector>
#include <forward_list>
#include <initializer_list>//std::initializer_list
#include <cmath>

template 
< 
typename KeyType,
typename DataType,
typename KeyHash = std::hash < KeyType > ,
typename KeyEqual = std::equal_to < KeyType >
>
class HashTbl {

      public:

            //template < class KeyType, class DataType >
            class HashEntry {//! Hash entry class

                  public:

                        HashEntry ( KeyType k_, DataType d_ ) : m_key( k_ ), m_data( d_ )
                        {/*Empty*/};

                        KeyType m_key;   //!< Stores the key for an entry.
                        DataType m_data; //!< Stores the data for an entry.

            };

            using Entry = HashEntry; /*< KeyType, DataType >*/ //! Alias

            //!<Contructors and destructor

            //HashTbl ( void ): m_size { DEFAULT_SIZE }, m_count { 0 }
            //{
             //     m_data_table.resize( DEFAULT_SIZE );
            //}

            HashTbl ( size_t tbl_size_ = DEFAULT_SIZE ): m_count { 0 }
            {
                m_size = next_prime( tbl_size_ ) ;
                m_data_table.resize( next_prime( tbl_size_ ) );

                std::cout<< "Contructor 1\n";
            }

            //virtual ~HashTbl (){
            //    delete [] m_data_table;
            //}

            //HashTbl ( const Hashtbl& ): 

            /*HashTbl ( std::initializer_list < Entry > ilist );

            HashTbl& operator= ( const Hashtbl & );

            HashTbl& operator= ( std::initializer_list < Entry > ilist );
            */
            /*
             *Insert an element present in Data d_, associating it with key k_
             @return True if insertion was succeed, False otherwise.
             */
            /*
            bool insert ( const KeyType & k_, const DataType & d_ ){
                KeyHash hashFunc;  // "Functor" for primary hash.
                KeyEqual equalFunc; // "Functor" for equality
                Entry new_entry(k_, d_);
                auto end(hashFunc(k_) % m_size);
                for(auto it(m_data_table[end].begin()); it != m_data_table[end].end()); it++){
                    if(true == equalFunc(it-> m_key. new_entry.m_key)){
                        it->m_data = d_;
                        m_count += 1;
                        return false;
                    }

                    m_count +=1;
                    if(size()/m_size > 1){
                        rehash();
                    }
                    m_data_table[end].push_front(new_entry);
                    return true;
                }


            }
            */
            /*
             * Removes an element identified for key k_
             @return True if the key was found, False otherwise.
             */
            /*
            bool erase ( const KeyType & k_ ){
                KeyHash hashFunc;
                KeyEqual equalFunc;
                auto end(hashFunc(k_) % m_size);
                if(m_data_table[end].empty()) return false;
                auto aux(m_data_table[end].before_begin());
                for(auto it(m_data_table[end].before_begin()); it != m_data_table[end].end(); it++){
                    if(true == equalFunc(it->m_key, k_)){
                        m_count -= 1;
                        m_data_table[end].erase_after(aux);
                        return true;
                    }
                }

                return false;
            }

            bool retrieve ( const KeyType & k_, DataType & d_ ) const{
                KeyHash hashFunc;
                KeyEqual equalFunc;
                auto end(hashFunc(k_) % m_size);
                for(auto it(m_data_table[end].begin()); it != m_data_table[end].end(); it++ ){
                    if(true == equalFunc(it->m_key, k_)){
                        d_ = it->m_data;
                        return true;
                    }
                }

                return false;
            }
            */
            /*!
             * Clear all the memory associated with collision lists from the table.
             * remove its elements
             */
            /*
            void clear ( void ){

                for(auto i(0u); i < m_size; i++){
                    m_data_table[i].clear();
                }

                m_count = 0;
                m_size = 0;
            }
            */
            /*!
              @return True if the hash is empty, or false otherwhise
              */

            //bool empty ( void ) const{
            //    return m_count == 0;
            //}

            /*! 
              @return the amount element sored ind the table.
             */

            size_t size ( void ) const{
                return m_count;
            }

           // DataType& at( const KeyType& k_ );

            //DataType& operator[] ( const KeyType& k_ );

            /*
             @return the amount of elements that are in collision list associated with key k_
             */
            /*
            size_t count ( const KeyType& k_ ) const{
                KeyHash hashFunc;

                auto end(hashFunc(k_) % m_size);
                size_t count = 0;
                for(auto it(m_data_table[i].begin(); it != m_data_table[i].end(); it++)){
                    count++;
                }

                return count;
            }
            */
            friend std::ostream& operator<< ( std::ostream & os, const HashTbl <KeyType, DataType, KeyHash, KeyEqual> & hashtbl ){
                for(auto i(0u); i < hashtbl.m_size; i++){
                    os << "[" << i "]";
                    for(auto it = hashtbl.m_data_table[i].begin(); it != hashtbl.m_data_table[i].end(); it++){
                        os << "-> " << it->m_data;
                    }
                    os <<std::endl;
                }

                return os;
            }

    //=== Private data.
      private:

            
            //!< Method that brings the next prime <= at the number.
            //!< Auxiliar method that return if the number is prime.
            bool Prime(int number){
                            
                            for(int i=2; i < number; i++){
                                if(number % i == 0){
                                    return false;
                                }
                            }
                            return true;
                        }

            size_t next_prime( size_t t_size )
            {
                  for( int i = 2; i <= sqrt( t_size ); i++){
                        if( t_size % i == 0 ){
                              return next_prime( t_size + 1 );
                        }
                  }
                  return t_size;
            }

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

                std::vector<std::forward_list< Entry > >*m_data_table_aux = new std::vector <foward_list <Entry>>[m_aux_size];

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
            std::vector <std::forward_list< Entry > >  m_data_table;
            //std::unique_ptr < std::forward_list< Entry > [] > m_data_table
            
            static const short DEFAULT_SIZE = 11;//! Hash table’s default size: 11 table entries.

};

#endif