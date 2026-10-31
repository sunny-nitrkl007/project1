///////////////////////////////////////////////////////////////////////////////
/// @file      AisJhm2WebResponses.h
/// @author    guanx
/// @date      July 26, 2018
/// @brief
///
///
/// @attention COPYRIGHT (C) 2013 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef AISJHM2WEBRESPONSES_H_
#define AISJHM2WEBRESPONSES_H_

#include <string>
#include <vector>
#include <std_types.h>
#include <jhm2/Jhm2Param/Jhm2Msg.h>
#include <jhm2/jsonCommon/JsonOutStream.h>
#include <interfaces/Coaching3x3Data/InterfaceTypes.h>
#include <interfaces/CoachingSummaryData/InterfaceTypes.h>

class Jhm2CoachingGradesCountMsg : public Jhm2Msg
{
public:
  Jhm2CoachingGradesCountMsg(int a, int c, int f) : A{a}, C{c}, F{f} {}

protected:
  bool getXml(std::ostream &xml) const override
  {
    xml << "<NotSupported/>";
    return true;
  }

  bool getJson(std::ostream &out) const override
  {
    JsonOutStream jostream;
    jostream.responseStart("exception_grades_count");
    jostream.String("A");
    jostream.Int(A);
    jostream.String("C");
    jostream.Int(C);
    jostream.String("F");
    jostream.Int(F);
    jostream.responseEnd();
    out << jostream;

    return true;
  }

private:
  int A, C, F;
};

class Jhm2CoachingTipsListMsg : public Jhm2Msg
{
public:
  Jhm2CoachingTipsListMsg(std::vector<CoachingTipOutput_t> s) : CoachingTipOutput_List{s} {}
  Jhm2CoachingTipsListMsg() = default;
  //since we are defining move semantices, we must define the copy functions and destructors, or else the compiler won't generate them
  Jhm2CoachingTipsListMsg(const Jhm2CoachingTipsListMsg &) = default;
  Jhm2CoachingTipsListMsg &operator=(const Jhm2CoachingTipsListMsg &) = default;

  //move constructor
  Jhm2CoachingTipsListMsg(Jhm2CoachingTipsListMsg &&src) : CoachingTipOutput_List{}
  {
    *this = std::move(src);
  }

  //move assignment
  Jhm2CoachingTipsListMsg &operator=(Jhm2CoachingTipsListMsg &&src)
  {
    CoachingTipOutput_List = std::move(src.CoachingTipOutput_List);
    return *this;
  }
  ~Jhm2CoachingTipsListMsg() = default;

protected:
  bool getXml(std::ostream &xml) const override
  {
    xml << "<NotSupported/>";
    return true;
  }

  bool getJson(std::ostream &out) const override
  {
    JsonOutStream jostream;
    jostream.StartObject();
    jostream.String("exceptions_list");
    jostream.StartArray();
    for (CoachingTipOutput_t tip : CoachingTipOutput_List)
    {
      jostream.StartObject();
      jostream("exception", tip);
      jostream.EndObject();
    }
    jostream.EndArray();
    jostream.EndObject();
    out << jostream;

    return true;
  }

private:
  std::vector<CoachingTipOutput_t> CoachingTipOutput_List;
};

//following is container of the tips and states that provides a zipped view
class Jhm2Coaching3x3DataMsg : public Jhm2Msg, public Coaching3x3DataStorage
{
public:
  Jhm2Coaching3x3DataMsg(std::vector<CoachingTipOutput_t> t, std::vector<std::vector<bool>> d) : Coaching3x3DataStorage(t, d) {}
  Jhm2Coaching3x3DataMsg() = default;
  Jhm2Coaching3x3DataMsg(Coaching3x3DataStorage c) : Coaching3x3DataStorage(c) {}
  //since we are defining move semantices, we must define the copy functions and destructors, or else the compiler won't generate them
  Jhm2Coaching3x3DataMsg(const Jhm2Coaching3x3DataMsg &) = default;
  Jhm2Coaching3x3DataMsg &operator=(const Jhm2Coaching3x3DataMsg &) = default;

  //move constructor
  Jhm2Coaching3x3DataMsg(Jhm2Coaching3x3DataMsg &&src)
  {
    *this = std::move(src);
  }

  //move assignment
  Jhm2Coaching3x3DataMsg &operator=(Jhm2Coaching3x3DataMsg &&src)
  {
    tips = std::move(src.tips);
    states = std::move(src.states);
    return *this;
  }
  ~Jhm2Coaching3x3DataMsg() = default;

  //ad-hoc iterator to iterate through the zip of tips and states
  struct zip_iterator
  {
    std::vector<CoachingTipOutput_t>::iterator tips_it;
    std::vector<std::vector<bool>>::iterator states_it;

    zip_iterator(std::vector<CoachingTipOutput_t>::iterator t, std::vector<std::vector<bool>>::iterator s) : tips_it{t}, states_it{s}
    {
    }

    zip_iterator &operator++()
    {
      ++tips_it;
      ++states_it;
      return *this;
    }

    bool operator==(const zip_iterator &other) const
    {
      //we want to stop iterating as soon as any of its sub iterators hit the end
      return other.tips_it == tips_it || other.states_it == states_it;
    }
    bool operator!=(const zip_iterator &other) const
    {
      return !(*this == other);
    }

    std::pair<CoachingTipOutput_t, std::vector<bool>> operator*()
    {
      return std::make_pair(*tips_it, *states_it);
    }
  };

  zip_iterator begin()
  {
    return zip_iterator(tips.begin(), states.begin());
  }

  zip_iterator end()
  {
    return zip_iterator(tips.end(), states.end());
  }

protected:
  bool getXml(std::ostream &xml) const override
  {
    xml << "<NotSupported/>";
    return true;
  }

  bool getJson(std::ostream &out) const override
  {
    JsonOutStream jostream;
    jostream.StartObject();
    jostream.String("dig_coach_xxx");
    jostream.StartArray();

    //iterate through the zip of tips and states -- tip-states is the tuple of (tip,state)
    for (auto tip_states : *this)
    {
      jostream.StartObject();
      {
        jostream("exception", std::get<0>(tip_states));
        jostream.String("dig_cycles");
        jostream.StartObject();
        std::string tmpstr = std::string{std::get<1>(tip_states)[0] ? "true" : "false"};
        jostream(std::string("dig0"), tmpstr);
        tmpstr = std::string{std::get<1>(tip_states)[1] ? "true" : "false"};
        jostream(std::string("dig1"), tmpstr);
        tmpstr = std::string{std::get<1>(tip_states)[2] ? "true" : "false"};
        jostream(std::string("dig2"), tmpstr);
        jostream.EndObject();
      }
      jostream.EndObject();
    }
    jostream.EndArray();
    jostream.EndObject();
    out << jostream;

    return true;
  }
};

#endif /* AISJHM2WEBRESPONSES_H_ */
