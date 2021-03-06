#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/address.h"
#include "ns3/Bsync_Common_headers.h"
#include "ns3/spectrum-manager.h"
#include "ns3/aodv-rtable.h"
#include <map>
#include <iostream>
#include <cassert>

namespace ns3 {

class Socket;
class Packet;

class Bsync_Client : public Application
{
public:
  static TypeId GetTypeId (void);
  Bsync_Client ();
  virtual ~Bsync_Client ();

  SpectrumManager * m_spectrumManager;
  std::vector<int> m_free_channels_list;
  bool **received_neighbour_channel_availability;
  bool *sent_neighbour_channel_availability;
  int* neighbour_status_array_client;

  //Ptr<Socket> m_socket;

  void startCG();
  void SetRemote (Address ip, uint16_t port);
  void SetRemote (Ipv4Address ip, uint16_t port);
  void SetRemote (Ipv6Address ip, uint16_t port);

  void SetDataSize (uint32_t dataSize);
  uint32_t GetDataSize (void) const;
  void SetFill (std::string fill);
  void SetFill (uint8_t fill, uint32_t dataSize);
  void SetFill (uint8_t *fill, uint32_t fillSize, uint32_t dataSize);

  TracedCallback<uint8_t*, int> m_SetAllottedColorsCallback_Client;

  void ScheduleTransmit (Time dt, Ptr<Packet> data, int sending_node_id);
  void ScheduleCommands (Time dt);
  void Client_Bsync_Logic();
  void Send (Ptr<Packet> data, int sending_node_id);

  std::vector<Ipv4Address> Routing_Nodes_Client;
  void GetRoutingTableClient(std::vector<Ipv4Address> received_Routing_Nodes, int node_id);
  std::vector<Ipv4Address> fetchReoutingNodesClient();

  std::ofstream output_client;

  int overhead_per_hello;
  int overhead_syn;
  int tot_hello_sent;
  int tot_sync_sent;


  int no_su;
  int no_pu;
  int current_depth;
  double* array_link_co;
  double* array_link_adj;
  double array_node_wt;
  double array_net_T;
  double opt_net_T;
  double array_net_Intf;
  double opt_net_Intf;
  void calc_node_t();
  void Obj();
  void link_co(int node_id, double snrval);
  void link_adj();
  double calc_backoff_cond();
  void exec_backoff_app();
  void conflict(Ptr<Node> current_node);
  void color_conflict();

  int m_self_node_id_client=0;
  bool *ConnectedNodeStatus_Client;
  uint8_t* client_CAT;
  bool neighbour_flag;

  int current_client_receive_color;

  std::vector<int> childvector;

  std::map<Ipv4Address, int> ip_nodeid_hash;

  Ptr<Socket> m_socket_client;//socket destructor called problem

protected:
  virtual void DoDispose (void);

private:

  virtual void StartApplication (void);
  virtual void StopApplication (void);

  void HandleRead (Ptr<Socket> socket);
  double f_simple( double x);
  double f_inver( double x);
  double increment_decrement(double x, double y);
  void reachedT(Ptr<Socket> socket);
  void transmitasONF(Ptr<Socket> socket);
  void MyFunction(SpectrumManager * sm);
  void MonitorSniffRxCall (Ptr<const Packet> packet, uint16_t channelFreqMhz, uint16_t channelNumber, uint32_t rate, bool isShortPreamble, double signalDbm, double noiseDbm);
  TracedCallback<SpectrumManager *, bool *, int> m_SetSpecAODVCallback_Client;
  TracedCallback<Ipv4Address, int> m_MyHelloReceiveCallback_Client;
  void ReceivedNeighbourSNR(Ipv4Address source, int node_id, bool ** received_status_array, int sent_hello_messages_till_now);
  void GetRoutingTable();

  uint16_t m_port;
  int tot_su;
  bool isSMupdated;
  int ref_node_id;
  Address m_local;
  uint32_t m_node_id;
  int tot_packet_sniffed_rx;
  double last_internal_timer_update;
  double last_internal_timer_val;
  double timestamp;
  int ref_flag;
  EventId m_event;

  uint32_t m_count;
  Time m_interval;
  uint32_t m_size;

  uint32_t m_dataSize;
  uint8_t *m_data;

  uint32_t m_sent;
  uint32_t m_received;
  Address m_peerAddress;
  uint16_t m_peerPort;
  EventId m_sendEvent;
  EventId m_ControlEvent;
  nState m_state;
  bool m_status;
  uint32_t period;
  double stop_time;
  double internal_timer;
  int m_period_count;
  /// Callbacks for tracing the packet Tx events
  TracedCallback<Ptr<const Packet> > m_txTrace;
};

} // namespace ns3
