#ifndef NARF_HISTUTILS_H
#define NARF_HISTUTILS_H

#include <boost/histogram.hpp>
#include "weighted_sum.h"
#include <ROOT/RResultPtr.hxx>

namespace narf {
  using namespace boost::histogram;

  template<typename Axis, typename... Axes>
  histogram<std::tuple<std::decay_t<Axis>, std::decay_t<Axes>...>, default_storage>
  make_histogram(Axis&& axis, Axes&&... axes) {
    return boost::histogram::make_histogram(std::forward<Axis>(axis), std::forward<Axes>(axes)...);
  }

  template<typename Axis, typename... Axes>
  histogram<std::tuple<std::decay_t<Axis>, std::decay_t<Axes>...>, dense_storage<accumulators::count<double, true>>>
  make_atomic_histogram(Axis&& axis, Axes&&... axes) {
    return make_histogram_with(dense_storage<accumulators::count<double, true>>(), std::forward<Axis>(axis), std::forward<Axes>(axes)...);
  }

  template<typename Axis, typename... Axes>
  histogram<std::tuple<std::decay_t<Axis>, std::decay_t<Axes>...>, dense_storage<narf::weighted_sum<double, true>>>
  make_atomic_histogram_with_error(Axis&& axis, Axes&&... axes) {
    return make_histogram_with(dense_storage<narf::weighted_sum<double, true>>(), std::forward<Axis>(axis), std::forward<Axes>(axes)...);
  }

  template<typename DFType, typename Helper, typename... ColTypes>
  ROOT::RDF::RResultPtr<typename std::decay_t<Helper>::Result_t>
  book_helper(DFType &df, Helper &&helper, const std::vector<std::string> &colnames) {
    return df.template Book<ColTypes...>(std::forward<Helper>(helper), colnames);
  }

//   template <typename HIST>
//   void boost_histogram_streamer(TBuffer &buf, void *objPtr) {
//     HIST *myObj = static_cast<HIST*>(objPtr);
//     if (buf.IsReading()) {
//       std::cout << "custom streamer reading" << std::endl;
// //       buf >> myObj->value1;
// //       buf >> myObj->value2;
//     } else {
//       std::cout << "custom streamer writing" << std::endl;
// //       buf << myObj->value1;
// //       buf << myObj->value2;
//     }
//   }
//
//   template <typename HIST>
//   void set_custom_streamer() {
//     TClass *cl = TClass::GetClass<HIST>();
//     cl->SetStreamerFunc(&boost_histogram_streamer<HIST>);
//   }

}

#endif
