#ifndef _XEP_MOOD_DATA_H_
#define  _XEP_MOOD_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char *ns_mood;

enum mood_mood_mood_t
{
  MOOD_MOOD_MOOD_AFRAID,
  MOOD_MOOD_MOOD_AMAZED,
  MOOD_MOOD_MOOD_ANGRY,
  MOOD_MOOD_MOOD_ANNOYED,
  MOOD_MOOD_MOOD_ANXIOUS,
  MOOD_MOOD_MOOD_AROUSED,
  MOOD_MOOD_MOOD_ASHAMED,
  MOOD_MOOD_MOOD_BORED,
  MOOD_MOOD_MOOD_BRAVE,
  MOOD_MOOD_MOOD_CALM,
  MOOD_MOOD_MOOD_COLD,
  MOOD_MOOD_MOOD_CONFUSED,
  MOOD_MOOD_MOOD_CONTENTED,
  MOOD_MOOD_MOOD_CRANKY,
  MOOD_MOOD_MOOD_CURIOUS,
  MOOD_MOOD_MOOD_DEPRESSED,
  MOOD_MOOD_MOOD_DISAPPOINTED,
  MOOD_MOOD_MOOD_DISGUSTED,
  MOOD_MOOD_MOOD_DISTRACTED,
  MOOD_MOOD_MOOD_EMBARRASSED,
  MOOD_MOOD_MOOD_EXCITED,
  MOOD_MOOD_MOOD_FLIRTATIOUS,
  MOOD_MOOD_MOOD_FRUSTRATED,
  MOOD_MOOD_MOOD_GRUMPY,
  MOOD_MOOD_MOOD_GUILTY,
  MOOD_MOOD_MOOD_HAPPY,
  MOOD_MOOD_MOOD_HOT,
  MOOD_MOOD_MOOD_HUMBLED,
  MOOD_MOOD_MOOD_HUMILIATED,
  MOOD_MOOD_MOOD_HUNGRY,
  MOOD_MOOD_MOOD_HURT,
  MOOD_MOOD_MOOD_IMPRESSED,
  MOOD_MOOD_MOOD_IN_AWE,
  MOOD_MOOD_MOOD_IN_LOVE,
  MOOD_MOOD_MOOD_INDIGNANT,
  MOOD_MOOD_MOOD_INTERESTED,
  MOOD_MOOD_MOOD_INTOXICATED,
  MOOD_MOOD_MOOD_INVINCIBLE,
  MOOD_MOOD_MOOD_JEALOUS,
  MOOD_MOOD_MOOD_LONELY,
  MOOD_MOOD_MOOD_MEAN,
  MOOD_MOOD_MOOD_MOODY,
  MOOD_MOOD_MOOD_NERVOUS,
  MOOD_MOOD_MOOD_NEUTRAL,
  MOOD_MOOD_MOOD_OFFENDED,
  MOOD_MOOD_MOOD_PLAYFUL,
  MOOD_MOOD_MOOD_PROUD,
  MOOD_MOOD_MOOD_RELIEVED,
  MOOD_MOOD_MOOD_REMORSEFUL,
  MOOD_MOOD_MOOD_RESTLESS,
  MOOD_MOOD_MOOD_SAD,
  MOOD_MOOD_MOOD_SARCASTIC,
  MOOD_MOOD_MOOD_SERIOUS,
  MOOD_MOOD_MOOD_SHOCKED,
  MOOD_MOOD_MOOD_SHY,
  MOOD_MOOD_MOOD_SICK,
  MOOD_MOOD_MOOD_SLEEPY,
  MOOD_MOOD_MOOD_STRESSED,
  MOOD_MOOD_MOOD_SURPRISED,
  MOOD_MOOD_MOOD_THIRSTY,
  MOOD_MOOD_MOOD_WORRIED,
};

enum mood_mood_mood_t enum_mood_mood_mood_from_string (const char *value);
const char *enum_mood_mood_mood_to_string (enum mood_mood_mood_t);

struct mood_mood_t
{
  enum mood_mood_mood_t fMood;
  char *fText;
};


struct mood_mood_t *mood_mood_decode (xmlreader_t * reader);
int mood_mood_encode (xmlwriter_t * writer, struct mood_mood_t *data);
void mood_mood_free (struct mood_mood_t *data);
#endif
