#pragma once

#include <chrono>
#include <map>

#ifndef DUJOUR_DEBUG
# define DUJOUR_DEBUG true
#endif

namespace dujour
{

  /**
   * @brief store cumulative time and number of execution of a function
   * 
   * @tparam T type for duration
   */
  template <typename T>
  struct counter
  {
    std::chrono::duration<T> time;
    std::size_t count;

    counter();
  };

  /**
   * @brief Construct a new counter<T>::counter object, set all elements to zero
   * 
   * @tparam T type for duration
   */
  template <typename T>
  counter<T>::counter()
  : time(std::chrono::duration<T>(0.)), count(0)
  {}

  /**
   * @brief object that mesure duration of its live time
   * 
   * @tparam T type for \ref counter
   * @tparam Clock clock type [default=`std::chrono::high_resolution_clock`]
   */
  template <typename T, typename Clock=std::chrono::high_resolution_clock>
  struct ephemere
  {
    std::chrono::time_point<Clock> start;
    counter<T> & store;

    ephemere ( counter<T> & );

    ~ephemere ();
  };

  /**
   * @brief Construct a new ephemere<T,Clock>::ephemere object and start chrono
   * 
   * @param c reference where store life duration and increment number of execution
   */
  template <typename T, typename Clock>
  ephemere<T,Clock>::ephemere ( counter<T> & c )
  : start(Clock::now()) , store(c)
  {}

  /**
   * @brief Destroy the ephemere<T,Clock>::ephemere object and mesure life duration and store it
   */
  template <typename T, typename Clock>
  ephemere<T,Clock>::~ephemere ()
  {
    auto end = Clock::now();
    store.time += end-start;
    ++store.count;
  }


  /**
   * @brief store different timer with a tag
   * 
   * @tparam T type for duration mesure
   * @tparam debug select if mesure or not
   * @tparam Clock type of clock
   */
  template <typename T, bool debug=DUJOUR_DEBUG, typename Clock=std::chrono::high_resolution_clock>
  struct scope_timer
  {};

  template <typename T, typename Clock>
  struct scope_timer<T,false,Clock>
  {
    static auto start ( const char * func );

    static std::map<const char*,counter<T>>
    cumulative_times ();
  };

  template <typename T, typename Clock>
  auto
  scope_timer<T,false,Clock>::start ( const char * func )
  {
    return false;
  }

  template <typename T, typename Clock>
  std::map<const char*,counter<T>>
  scope_timer<T,false,Clock>::cumulative_times ()
  {
    return std::map<const char*,counter<T>>();
  }


  template <typename T, typename Clock>
  struct scope_timer<T,true,Clock>
  {
    static std::map<const char*,counter<T>> _cumulative_times;

    static auto start ( const char * func );

    static std::map<const char*,counter<T>>
    cumulative_times ();
  };

  template <typename T, typename Clock>
  std::map<const char*,counter<T>> scope_timer<T,true,Clock>::_cumulative_times;

  template <typename T, typename Clock>
  auto
  scope_timer<T,true,Clock>::start ( const char * func )
  {
    return ephemere<T,Clock>(_cumulative_times[func]);
  }

  template <typename T, typename Clock>
  std::map<const char*,counter<T>>
  scope_timer<T,true,Clock>::cumulative_times ()
  {
    return _cumulative_times;
  }

} // namespace dujour

