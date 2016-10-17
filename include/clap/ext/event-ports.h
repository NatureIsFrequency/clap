#ifndef CLAP_EVENT_PORTS_H
# define CLAP_EVENT_PORTS_H

# include "../clap.h"

# define CLAP_EXT_EVENT_PORTS "clap/event-ports"

struct clap_audio_port_info
{
  int32_t id;
  bool    is_input;
  char    name[CLAP_NAME_SIZE];

  /* If true, then this is a virtual port which can be cloned
   * and connected multiple times.
   * Only useful for input ports. */
  bool is_cloneable;
};

struct clap_plugin_event_ports
{
  /* number of ports, including inputs and outputs */
  int32_t (*get_count)(struct clap_plugin         *plugin);

  /* get info about about an event port. */
  void (*get_info)(struct clap_plugin             *plugin,
                   int32_t                         index,
                   struct clap_event_port_info    *info);

  /* Clones a clonable port.
   * On success returns a unique port id, for the cloned port.
   * On failure, returns -1.
   * user_name is a string provided by the host to tell the
   * plugin how to name the new cloned port.
   */
  int32_t (*clone_port)(struct clap_plugin *plugin,
                        int32_t             port_id,
                        const char         *user_name);

  /* When the host is done with a cloned port, it can call
   * release_port() to release the resources. */
  int32_t (*release_port)(struct clap_plugin *plugin,
                          int32_t             port_id);
};

#endif /* !EVENT_PORTS_H */