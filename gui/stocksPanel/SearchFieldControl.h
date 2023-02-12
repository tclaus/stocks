/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef SEARCHFIELD_H
#define SEARCHFIELD_H

#include <SupportDefs.h>
#include <TextControl.h>

class SearchFieldControl : public BTextControl {
public:
  SearchFieldControl();
  virtual ~SearchFieldControl();

private:
};

enum {
  M_SET_STOCK = 'setS'

};

#endif // SEARCHFIELD_H
