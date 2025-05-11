#pragma once

// This header protects against multiple definitions by creating a wrapper macro
// that only expands to Q_OBJECT in one compilation unit

#ifdef DEFINE_QOBJECT_ONCE
#define MY_Q_OBJECT Q_OBJECT
#else
#define MY_Q_OBJECT
#endif
