/*
 * Copyright 2010-2011, Haiku, Inc.
 * Distributed under the terms of the MIT License.
 */
#ifndef _B_TIME_UNIT_FORMAT_H_
#define _B_TIME_UNIT_FORMAT_H_


#include <Format.h>
#include <SupportDefs.h>


class BString;

#ifndef U_ICU_NAMESPACE
  #define U_ICU_NAMESPACE icu
#endif
namespace U_ICU_NAMESPACE {
	class TimeUnitFormat;
}


enum time_unit_style {
	B_TIME_UNIT_ABBREVIATED,	// e.g. '5 hrs.'
	B_TIME_UNIT_FULL,			// e.g. '5 hours'
};


enum time_unit_element {
	B_TIME_UNIT_YEAR,
	B_TIME_UNIT_MONTH,
	B_TIME_UNIT_WEEK,
	B_TIME_UNIT_DAY,
	B_TIME_UNIT_HOUR,
	B_TIME_UNIT_MINUTE,
	B_TIME_UNIT_SECOND,

	B_TIME_UNIT_LAST = B_TIME_UNIT_SECOND
};


class BTimeUnitFormat : public BFormat {
	typedef	BFormat				Inherited;

public:
								BTimeUnitFormat(const time_unit_style style =
									B_TIME_UNIT_FULL);
								BTimeUnitFormat(const BLanguage& language,
									const BFormattingConventions& conventions,
									const time_unit_style style = B_TIME_UNIT_FULL);
								BTimeUnitFormat(const BTimeUnitFormat& other);
	virtual						~BTimeUnitFormat();

			status_t			Format(BString& buffer,
									const int32 value,
									const time_unit_element unit
									) const;

private:
			U_ICU_NAMESPACE::TimeUnitFormat*	fFormatter;
};


#endif
