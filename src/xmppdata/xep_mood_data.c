#include "xep_mood_data.h"
#include "helpers.h"
#include "errors.h"

const char *ns_mood = "http://jabber.org/protocol/mood";

struct mood_mood_t *
mood_mood_decode (xmlreader_t * reader)
{
  struct mood_mood_t *elm = NULL;
  elm = malloc (sizeof (struct mood_mood_t));
  if (elm == NULL)
    fatal ("mood_mood_t: malloc failed");
  memset (elm, 0, sizeof (struct mood_mood_t));
  int type = 0;
  while (1)
    {
      type = xmlreader_next (reader);
      if (type == XML_END_ELEMENT)
	break;
      if (type == XML_ERROR)
	return NULL;
      if (type == XML_START_ELEMENT)
	{
	  const char *namespace = xmlreader_get_namespace (reader);
	  const char *name = xmlreader_get_name (reader);
	  if ((strcmp (name, "text") == 0)
	      && (strcmp (namespace, ns_mood) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fText = (char *) value;
	    }
	  else if (strcmp (namespace, ns_mood) != 0)
	    {
	      elm->fMood = enum_mood_mood_mood_from_string (name);
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	    }
	}
    }
  return elm;
}

int
mood_mood_encode (xmlwriter_t * writer, struct mood_mood_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_mood, "mood");
  if (err != 0)
    return err;
  if (elm->fMood != 0)
    {
      const char *name = enum_mood_mood_mood_to_string (elm->fMood);
      err = xmlwriter_simple_element (writer, ns_mood, name, NULL);
      if (err != 0)
	return err;
    }
  if (elm->fText != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_mood, "text", elm->fText);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
mood_mood_free (struct mood_mood_t *data)
{
  if (data == NULL)
    return;
  if (data->fMood != 0)
    {
    }
  if (data->fText != NULL)
    {
      free (data->fText);
    }
  free (data);
}

enum mood_mood_mood_t
enum_mood_mood_mood_from_string (const char *value)
{
  if (strcmp (value, "afraid") == 0)
    return MOOD_MOOD_MOOD_AFRAID;
  else if (strcmp (value, "amazed") == 0)
    return MOOD_MOOD_MOOD_AMAZED;
  else if (strcmp (value, "angry") == 0)
    return MOOD_MOOD_MOOD_ANGRY;
  else if (strcmp (value, "annoyed") == 0)
    return MOOD_MOOD_MOOD_ANNOYED;
  else if (strcmp (value, "anxious") == 0)
    return MOOD_MOOD_MOOD_ANXIOUS;
  else if (strcmp (value, "aroused") == 0)
    return MOOD_MOOD_MOOD_AROUSED;
  else if (strcmp (value, "ashamed") == 0)
    return MOOD_MOOD_MOOD_ASHAMED;
  else if (strcmp (value, "bored") == 0)
    return MOOD_MOOD_MOOD_BORED;
  else if (strcmp (value, "brave") == 0)
    return MOOD_MOOD_MOOD_BRAVE;
  else if (strcmp (value, "calm") == 0)
    return MOOD_MOOD_MOOD_CALM;
  else if (strcmp (value, "cold") == 0)
    return MOOD_MOOD_MOOD_COLD;
  else if (strcmp (value, "confused") == 0)
    return MOOD_MOOD_MOOD_CONFUSED;
  else if (strcmp (value, "contented") == 0)
    return MOOD_MOOD_MOOD_CONTENTED;
  else if (strcmp (value, "cranky") == 0)
    return MOOD_MOOD_MOOD_CRANKY;
  else if (strcmp (value, "curious") == 0)
    return MOOD_MOOD_MOOD_CURIOUS;
  else if (strcmp (value, "depressed") == 0)
    return MOOD_MOOD_MOOD_DEPRESSED;
  else if (strcmp (value, "disappointed") == 0)
    return MOOD_MOOD_MOOD_DISAPPOINTED;
  else if (strcmp (value, "disgusted") == 0)
    return MOOD_MOOD_MOOD_DISGUSTED;
  else if (strcmp (value, "distracted") == 0)
    return MOOD_MOOD_MOOD_DISTRACTED;
  else if (strcmp (value, "embarrassed") == 0)
    return MOOD_MOOD_MOOD_EMBARRASSED;
  else if (strcmp (value, "excited") == 0)
    return MOOD_MOOD_MOOD_EXCITED;
  else if (strcmp (value, "flirtatious") == 0)
    return MOOD_MOOD_MOOD_FLIRTATIOUS;
  else if (strcmp (value, "frustrated") == 0)
    return MOOD_MOOD_MOOD_FRUSTRATED;
  else if (strcmp (value, "grumpy") == 0)
    return MOOD_MOOD_MOOD_GRUMPY;
  else if (strcmp (value, "guilty") == 0)
    return MOOD_MOOD_MOOD_GUILTY;
  else if (strcmp (value, "happy") == 0)
    return MOOD_MOOD_MOOD_HAPPY;
  else if (strcmp (value, "hot") == 0)
    return MOOD_MOOD_MOOD_HOT;
  else if (strcmp (value, "humbled") == 0)
    return MOOD_MOOD_MOOD_HUMBLED;
  else if (strcmp (value, "humiliated") == 0)
    return MOOD_MOOD_MOOD_HUMILIATED;
  else if (strcmp (value, "hungry") == 0)
    return MOOD_MOOD_MOOD_HUNGRY;
  else if (strcmp (value, "hurt") == 0)
    return MOOD_MOOD_MOOD_HURT;
  else if (strcmp (value, "impressed") == 0)
    return MOOD_MOOD_MOOD_IMPRESSED;
  else if (strcmp (value, "in_awe") == 0)
    return MOOD_MOOD_MOOD_IN_AWE;
  else if (strcmp (value, "in_love") == 0)
    return MOOD_MOOD_MOOD_IN_LOVE;
  else if (strcmp (value, "indignant") == 0)
    return MOOD_MOOD_MOOD_INDIGNANT;
  else if (strcmp (value, "interested") == 0)
    return MOOD_MOOD_MOOD_INTERESTED;
  else if (strcmp (value, "intoxicated") == 0)
    return MOOD_MOOD_MOOD_INTOXICATED;
  else if (strcmp (value, "invincible") == 0)
    return MOOD_MOOD_MOOD_INVINCIBLE;
  else if (strcmp (value, "jealous") == 0)
    return MOOD_MOOD_MOOD_JEALOUS;
  else if (strcmp (value, "lonely") == 0)
    return MOOD_MOOD_MOOD_LONELY;
  else if (strcmp (value, "mean") == 0)
    return MOOD_MOOD_MOOD_MEAN;
  else if (strcmp (value, "moody") == 0)
    return MOOD_MOOD_MOOD_MOODY;
  else if (strcmp (value, "nervous") == 0)
    return MOOD_MOOD_MOOD_NERVOUS;
  else if (strcmp (value, "neutral") == 0)
    return MOOD_MOOD_MOOD_NEUTRAL;
  else if (strcmp (value, "offended") == 0)
    return MOOD_MOOD_MOOD_OFFENDED;
  else if (strcmp (value, "playful") == 0)
    return MOOD_MOOD_MOOD_PLAYFUL;
  else if (strcmp (value, "proud") == 0)
    return MOOD_MOOD_MOOD_PROUD;
  else if (strcmp (value, "relieved") == 0)
    return MOOD_MOOD_MOOD_RELIEVED;
  else if (strcmp (value, "remorseful") == 0)
    return MOOD_MOOD_MOOD_REMORSEFUL;
  else if (strcmp (value, "restless") == 0)
    return MOOD_MOOD_MOOD_RESTLESS;
  else if (strcmp (value, "sad") == 0)
    return MOOD_MOOD_MOOD_SAD;
  else if (strcmp (value, "sarcastic") == 0)
    return MOOD_MOOD_MOOD_SARCASTIC;
  else if (strcmp (value, "serious") == 0)
    return MOOD_MOOD_MOOD_SERIOUS;
  else if (strcmp (value, "shocked") == 0)
    return MOOD_MOOD_MOOD_SHOCKED;
  else if (strcmp (value, "shy") == 0)
    return MOOD_MOOD_MOOD_SHY;
  else if (strcmp (value, "sick") == 0)
    return MOOD_MOOD_MOOD_SICK;
  else if (strcmp (value, "sleepy") == 0)
    return MOOD_MOOD_MOOD_SLEEPY;
  else if (strcmp (value, "stressed") == 0)
    return MOOD_MOOD_MOOD_STRESSED;
  else if (strcmp (value, "surprised") == 0)
    return MOOD_MOOD_MOOD_SURPRISED;
  else if (strcmp (value, "thirsty") == 0)
    return MOOD_MOOD_MOOD_THIRSTY;
  else if (strcmp (value, "worried") == 0)
    return MOOD_MOOD_MOOD_WORRIED;
  return 0;
}

const char *
enum_mood_mood_mood_to_string (enum mood_mood_mood_t value)
{
  switch (value)
    {
    case MOOD_MOOD_MOOD_AFRAID:
      return "afraid";
    case MOOD_MOOD_MOOD_AMAZED:
      return "amazed";
    case MOOD_MOOD_MOOD_ANGRY:
      return "angry";
    case MOOD_MOOD_MOOD_ANNOYED:
      return "annoyed";
    case MOOD_MOOD_MOOD_ANXIOUS:
      return "anxious";
    case MOOD_MOOD_MOOD_AROUSED:
      return "aroused";
    case MOOD_MOOD_MOOD_ASHAMED:
      return "ashamed";
    case MOOD_MOOD_MOOD_BORED:
      return "bored";
    case MOOD_MOOD_MOOD_BRAVE:
      return "brave";
    case MOOD_MOOD_MOOD_CALM:
      return "calm";
    case MOOD_MOOD_MOOD_COLD:
      return "cold";
    case MOOD_MOOD_MOOD_CONFUSED:
      return "confused";
    case MOOD_MOOD_MOOD_CONTENTED:
      return "contented";
    case MOOD_MOOD_MOOD_CRANKY:
      return "cranky";
    case MOOD_MOOD_MOOD_CURIOUS:
      return "curious";
    case MOOD_MOOD_MOOD_DEPRESSED:
      return "depressed";
    case MOOD_MOOD_MOOD_DISAPPOINTED:
      return "disappointed";
    case MOOD_MOOD_MOOD_DISGUSTED:
      return "disgusted";
    case MOOD_MOOD_MOOD_DISTRACTED:
      return "distracted";
    case MOOD_MOOD_MOOD_EMBARRASSED:
      return "embarrassed";
    case MOOD_MOOD_MOOD_EXCITED:
      return "excited";
    case MOOD_MOOD_MOOD_FLIRTATIOUS:
      return "flirtatious";
    case MOOD_MOOD_MOOD_FRUSTRATED:
      return "frustrated";
    case MOOD_MOOD_MOOD_GRUMPY:
      return "grumpy";
    case MOOD_MOOD_MOOD_GUILTY:
      return "guilty";
    case MOOD_MOOD_MOOD_HAPPY:
      return "happy";
    case MOOD_MOOD_MOOD_HOT:
      return "hot";
    case MOOD_MOOD_MOOD_HUMBLED:
      return "humbled";
    case MOOD_MOOD_MOOD_HUMILIATED:
      return "humiliated";
    case MOOD_MOOD_MOOD_HUNGRY:
      return "hungry";
    case MOOD_MOOD_MOOD_HURT:
      return "hurt";
    case MOOD_MOOD_MOOD_IMPRESSED:
      return "impressed";
    case MOOD_MOOD_MOOD_IN_AWE:
      return "in_awe";
    case MOOD_MOOD_MOOD_IN_LOVE:
      return "in_love";
    case MOOD_MOOD_MOOD_INDIGNANT:
      return "indignant";
    case MOOD_MOOD_MOOD_INTERESTED:
      return "interested";
    case MOOD_MOOD_MOOD_INTOXICATED:
      return "intoxicated";
    case MOOD_MOOD_MOOD_INVINCIBLE:
      return "invincible";
    case MOOD_MOOD_MOOD_JEALOUS:
      return "jealous";
    case MOOD_MOOD_MOOD_LONELY:
      return "lonely";
    case MOOD_MOOD_MOOD_MEAN:
      return "mean";
    case MOOD_MOOD_MOOD_MOODY:
      return "moody";
    case MOOD_MOOD_MOOD_NERVOUS:
      return "nervous";
    case MOOD_MOOD_MOOD_NEUTRAL:
      return "neutral";
    case MOOD_MOOD_MOOD_OFFENDED:
      return "offended";
    case MOOD_MOOD_MOOD_PLAYFUL:
      return "playful";
    case MOOD_MOOD_MOOD_PROUD:
      return "proud";
    case MOOD_MOOD_MOOD_RELIEVED:
      return "relieved";
    case MOOD_MOOD_MOOD_REMORSEFUL:
      return "remorseful";
    case MOOD_MOOD_MOOD_RESTLESS:
      return "restless";
    case MOOD_MOOD_MOOD_SAD:
      return "sad";
    case MOOD_MOOD_MOOD_SARCASTIC:
      return "sarcastic";
    case MOOD_MOOD_MOOD_SERIOUS:
      return "serious";
    case MOOD_MOOD_MOOD_SHOCKED:
      return "shocked";
    case MOOD_MOOD_MOOD_SHY:
      return "shy";
    case MOOD_MOOD_MOOD_SICK:
      return "sick";
    case MOOD_MOOD_MOOD_SLEEPY:
      return "sleepy";
    case MOOD_MOOD_MOOD_STRESSED:
      return "stressed";
    case MOOD_MOOD_MOOD_SURPRISED:
      return "surprised";
    case MOOD_MOOD_MOOD_THIRSTY:
      return "thirsty";
    case MOOD_MOOD_MOOD_WORRIED:
      return "worried";
    }
  return NULL;
}
