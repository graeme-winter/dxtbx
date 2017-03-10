/*
 * experiment_list.cc
 *
 *  Copyright (C) 2017 Diamond Light Source
 *
 *  Author: James Parkhurst
 *
 *  This code is distributed under the BSD license, a copy of which is
 *  included in the root directory of this package.
 */
#include <boost/python.hpp>
#include <boost/python/def.hpp>
#include <boost/python/slice.hpp>
#include <string>
#include <sstream>
#include <scitbx/constants.h>
#include <scitbx/boost_python/slice.h>
#include <scitbx/boost_python/utils.h>
#include <dxtbx/model/experiment_list.h>
#include <dxtbx/model/boost_python/to_from_dict.h>

namespace dxtbx { namespace model { namespace boost_python {

  using namespace boost::python;

  static
  ExperimentList* make_experiment_list(boost::python::object items) {

    ExperimentList *experiment = new ExperimentList();

    for (std::size_t i = 0; i < boost::python::len(items); ++i) {
      experiment->append(boost::python::extract<Experiment>(items[i])());
    }


    return experiment;
  }


  struct ExperimentListPickleSuite : boost::python::pickle_suite {
    static
    boost::python::tuple getinitargs(const ExperimentList &obj) {
      boost::python::list experiments;
      for (std::size_t i = 0; i < obj.size(); ++i) {
        experiments.append(obj[i]);
      }
      return boost::python::make_tuple(experiments);
    }
  };

  template <>
  boost::python::dict to_dict<ExperimentList>(const ExperimentList &obj) {
    boost::python::dict result;
    return result;
  }

  template <>
  ExperimentList* from_dict<ExperimentList>(boost::python::dict obj) {
    return new ExperimentList();
  }

  /**
   * Return function pointers to overrides for different types
   */
  struct experiment_list_contains_pointers {

    typedef bool (ExperimentList::*beam_type)(const boost::shared_ptr<Beam>&)const;
    typedef bool (ExperimentList::*detector_type)(const boost::shared_ptr<Detector>&)const;
    typedef bool (ExperimentList::*goniometer_type)(const boost::shared_ptr<Goniometer>&)const;
    typedef bool (ExperimentList::*scan_type)(const boost::shared_ptr<Scan>&)const;
    typedef bool (ExperimentList::*crystal_type)(const boost::shared_ptr<Crystal>&)const;
    typedef bool (ExperimentList::*object_type)(boost::python::object)const;

    static beam_type beam() {
      return &ExperimentList::contains;
    }

    static detector_type detector() {
      return &ExperimentList::contains;
    }

    static goniometer_type goniometer() {
      return &ExperimentList::contains;
    }

    static scan_type scan() {
      return &ExperimentList::contains;
    }

    static crystal_type crystal() {
      return &ExperimentList::contains;
    }

    static object_type object() {
      return &ExperimentList::contains;
    }

  };

  /**
   * Return function pointers to overrides for different types
   */
  struct experiment_list_replace_pointers {

    typedef void (ExperimentList::*beam_type)(
        boost::shared_ptr<Beam>,
        boost::shared_ptr<Beam>);
    typedef void (ExperimentList::*detector_type)(
        boost::shared_ptr<Detector>,
        boost::shared_ptr<Detector>);
    typedef void (ExperimentList::*goniometer_type)(
        boost::shared_ptr<Goniometer>,
        boost::shared_ptr<Goniometer>);
    typedef void (ExperimentList::*scan_type)(
        boost::shared_ptr<Scan>,
        boost::shared_ptr<Scan>);
    typedef void (ExperimentList::*crystal_type)(
        boost::shared_ptr<Crystal>,
        boost::shared_ptr<Crystal>);
    typedef void (ExperimentList::*object_type)(
        boost::python::object,
        boost::python::object);

    static beam_type beam() {
      return &ExperimentList::replace;
    }

    static detector_type detector() {
      return &ExperimentList::replace;
    }

    static goniometer_type goniometer() {
      return &ExperimentList::replace;
    }

    static scan_type scan() {
      return &ExperimentList::replace;
    }

    static crystal_type crystal() {
      return &ExperimentList::replace;
    }

    static object_type object() {
      return &ExperimentList::replace;
    }

  };

  /**
   * Return function pointers to overrides for different types
   */
  struct experiment_list_indices_pointers {

    typedef scitbx::af::shared<std::size_t> (ExperimentList::*beam_type)(
        const boost::shared_ptr<Beam>&)const;
    typedef scitbx::af::shared<std::size_t> (ExperimentList::*detector_type)(
        const boost::shared_ptr<Detector>&)const;
    typedef scitbx::af::shared<std::size_t> (ExperimentList::*goniometer_type)(
        const boost::shared_ptr<Goniometer>&)const;
    typedef scitbx::af::shared<std::size_t> (ExperimentList::*scan_type)(
        const boost::shared_ptr<Scan>&)const;
    typedef scitbx::af::shared<std::size_t> (ExperimentList::*crystal_type)(
        const boost::shared_ptr<Crystal>&)const;
    typedef scitbx::af::shared<std::size_t> (ExperimentList::*object_type)(
        boost::python::object)const;

    static beam_type beam() {
      return &ExperimentList::indices;
    }

    static detector_type detector() {
      return &ExperimentList::indices;
    }

    static goniometer_type goniometer() {
      return &ExperimentList::indices;
    }

    static scan_type scan() {
      return &ExperimentList::indices;
    }

    static crystal_type crystal() {
      return &ExperimentList::indices;
    }

    static object_type object() {
      return &ExperimentList::indices;
    }

  };

  void experiment_list_setitem(ExperimentList &self, std::size_t n, Experiment item) {
    if (n >= self.size()) {
      scitbx::boost_python::raise_index_error();
    }
    self[n] = item;
  }

  Experiment& experiment_list_getitem(ExperimentList &self, std::size_t n) {
    if (n >= self.size()) {
      scitbx::boost_python::raise_index_error();
    }
    return self[n];
  }

  ExperimentList experiment_list_getitem_slice(const ExperimentList &self, slice s) {
    scitbx::boost_python::adapted_slice as(s, self.size());
    ExperimentList result;
    for (std::size_t i = as.start;
         i < as.stop && i < self.size();
         i += as.step) {
      result.append(self[i]);
    }
    return result;
  }

  void experiment_list_delitem(ExperimentList &self, std::size_t n) {
    if (n >= self.size()) {
      scitbx::boost_python::raise_index_error();
    }
    self.erase(n);
  }

  void export_experiment_list()
  {
    class_ <ExperimentList> ("ExperimentList")
      .def("__init__",
          make_constructor(
          &make_experiment_list,
          default_call_policies()))
      .def("append", &ExperimentList::append)
      .def("extend", &ExperimentList::extend)
      .def("clear", &ExperimentList::clear)
      .def("empty", &ExperimentList::empty)
      .def("__getitem__", &experiment_list_getitem, return_internal_reference<>())
      .def("__getitem__", &experiment_list_getitem_slice)
      .def("__setitem__", &experiment_list_setitem)
      .def("__delitem__", &experiment_list_delitem)
      .def("__iter__", iterator<ExperimentList, return_internal_reference<> >())
      .def("__contains__", experiment_list_contains_pointers::beam())
      .def("__contains__", experiment_list_contains_pointers::detector())
      .def("__contains__", experiment_list_contains_pointers::goniometer())
      .def("__contains__", experiment_list_contains_pointers::scan())
      .def("__contains__", experiment_list_contains_pointers::crystal())
      .def("__contains__", experiment_list_contains_pointers::object())
      .def("replace", experiment_list_replace_pointers::beam())
      .def("replace", experiment_list_replace_pointers::detector())
      .def("replace", experiment_list_replace_pointers::goniometer())
      .def("replace", experiment_list_replace_pointers::scan())
      .def("replace", experiment_list_replace_pointers::crystal())
      .def("replace", experiment_list_replace_pointers::object())
      .def("indices", experiment_list_indices_pointers::beam())
      .def("indices", experiment_list_indices_pointers::detector())
      .def("indices", experiment_list_indices_pointers::goniometer())
      .def("indices", experiment_list_indices_pointers::scan())
      .def("indices", experiment_list_indices_pointers::crystal())
      .def("indices", experiment_list_indices_pointers::object())
      .def("where", &ExperimentList::where, (
        arg("beam")       = boost::shared_ptr<Beam>(),
        arg("detector")   = boost::shared_ptr<Detector>(),
        arg("goniometer") = boost::shared_ptr<Goniometer>(),
        arg("scan")       = boost::shared_ptr<Scan>(),
        arg("crystal")    = boost::shared_ptr<Crystal>(),
        arg("profile")    = boost::python::object(),
        arg("imageset")   = boost::python::object()))
      .def("is_consistent", &ExperimentList::is_consistent)
      .def("__len__", &ExperimentList::size)
      .def("to_dict", &to_dict<ExperimentList>)
      .def("from_dict", &from_dict<ExperimentList>,
        return_value_policy<manage_new_object>())
      .staticmethod("from_dict")
      .def_pickle(ExperimentListPickleSuite());
  }

}}} // namespace = dxtbx::model::boost_python
