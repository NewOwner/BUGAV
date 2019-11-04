using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using DarkUI.Forms;

using System.Net;
using System.Net.Sockets;

namespace BUGAV {
    public partial class Form_FilterNetworkRule : DarkForm {
        public Form_FilterNetworkRule() {
            InitializeComponent();
        }
        private void FilterNetworkRule_Button_AddRule_Click(object sender, EventArgs e) {

            RuleComponent compAction = new RuleComponent(RuleComponentType.action, FilterNetworkRule_comboBox_Action.Text);
            RuleComponent compDirection = new RuleComponent(RuleComponentType.direction, FilterNetworkRule_comboBox_Direction.Text);
            RuleComponent compEtherType = new RuleComponent(RuleComponentType.ether_type, FilterNetworkRule_comboBox_EtherType.Text);
            RuleComponent compIpNextProtocol = new RuleComponent(RuleComponentType.ip_next_protocol, FilterNetworkRule_comboBox_IpNextProtocol.Text);
            RuleComponent compSourceIp = new RuleComponent(RuleComponentType.source_ip, FilterNetworkRule_textBox_SourceIp.Text);
            RuleComponent compDestinationIp = new RuleComponent(RuleComponentType.destination_ip, FilterNetworkRule_textBox_DestinationIp.Text);
            RuleComponent compSourcePort = new RuleComponent(RuleComponentType.source_port, FilterNetworkRule_textBox_SourcePort.Text);
            RuleComponent compDestinationPort = new RuleComponent(RuleComponentType.destination_port, FilterNetworkRule_textBox_DestinationPort.Text);

            NetRules newRule = new NetRules(compAction,
                                            compDirection,
                                            compEtherType,
                                            compIpNextProtocol,
                                            compSourceIp,
                                            compDestinationIp,
                                            compSourcePort,
                                            compDestinationPort);

        }
        private void FilterNetworkRule_Button_Cancel_Click(object sender, EventArgs e) {
            this.Close();
        }

    }
    public enum RuleComponentType {
        action,
        direction,
        ether_type,
        ip_next_protocol,
        source_ip,
        destination_ip,
        source_port,
        destination_port
    }
    public class RuleComponent {
        RuleComponentType type;
        string fieldStr;
        public IEnumerable<byte> fieldBytes;

        public RuleComponent(RuleComponentType _type, string _fieldStr) {
            type = _type;
            fieldStr = _fieldStr;
            ToBytes();
        }
        public void ToBytes() {
            byte[] arr = null;
            IPAddress address = null;
            ushort port;
            switch (type) {
                case RuleComponentType.action:
                    if(fieldStr == "Alert") { arr = new byte[] { 0x01 }; } 
                    else if(fieldStr == "Drop") { arr = new byte[] { 0x02 }; }
                    else if(fieldStr == "Ignore") { arr = new byte[] { 0x00 }; }
                    break;
                case RuleComponentType.direction: 
                    if(fieldStr == "From") { arr = new byte[] { 0x01 }; } 
                    else if(fieldStr == "To") { arr = new byte[] { 0x02 }; }
                    else if(fieldStr == "Ignore") { arr = new byte[] { 0x00 }; }
                    break;
                case RuleComponentType.ether_type:
                    if(fieldStr == "IP") { arr = new byte[] { 0x08, 0x00 }; } 
                    else if(fieldStr == "ARP") { arr = new byte[] { 0x08, 0x06 }; }
                    else if(fieldStr == "Ignore") { arr = new byte[] { 0x00,0x00 }; }
                    break;
                case RuleComponentType.ip_next_protocol: 
                    if(fieldStr == "ICMP") { arr = new byte[] { 0x01 }; } 
                    else if(fieldStr == "IGMP") { arr = new byte[] { 0x02 }; }
                    else if(fieldStr == "UDP") { arr = new byte[] { 0x11 }; }
                    else if(fieldStr == "TCP") { arr = new byte[] { 0x06 }; }
                    else if(fieldStr == "Ignore") { arr = new byte[] { 0x00 }; }
                    break;
                case RuleComponentType.source_ip:
                    if (fieldStr == "Ignore") { arr = new byte[] { 0x00, 0x00, 0x00, 0x00 }; }
                    else{
                        address = IPAddress.Parse(fieldStr);
                        arr = address.GetAddressBytes();
                    }
                    break;
                case RuleComponentType.destination_ip:
                    if (fieldStr == "Ignore") { arr = new byte[] { 0x00, 0x00, 0x00, 0x00 }; } 
                    else {
                        address = IPAddress.Parse(fieldStr);
                        arr = address.GetAddressBytes();
                    }
                    break;
                case RuleComponentType.source_port:
                    if (fieldStr == "Ignore") { arr = new byte[] { 0x00, 0x00 }; } 
                    else {
                        port = ushort.Parse(fieldStr);
                        arr = BitConverter.GetBytes(port);
                    }
                    break;
                case RuleComponentType.destination_port:
                    if (fieldStr == "Ignore") { arr = new byte[] { 0x00, 0x00 }; } 
                    else {
                        port = ushort.Parse(fieldStr);
                        arr = BitConverter.GetBytes(port);
                    }
                    break;
            }
            Console.WriteLine(BitConverter.ToString(arr));
            fieldBytes = arr.Cast<byte>();
        }


    }
    public class NetRules {
        RuleComponent compAction;
        RuleComponent compDirection;
        RuleComponent compEtherType;
        RuleComponent compIpNextProtocol;
        RuleComponent compSourceIp;
        RuleComponent compDestinationIp;
        RuleComponent compSourcePort;
        RuleComponent compDestinationPort;
        IEnumerable<byte> ruleBytes;

        public NetRules(
        RuleComponent _compAction,
        RuleComponent _compDirection,
        RuleComponent _compEtherType,
        RuleComponent _compIpNextProtocol,
        RuleComponent _compSourceIp,
        RuleComponent _compDestinationIp,
        RuleComponent _compSourcePort,
        RuleComponent _compDestinationPort
            ) {
            compAction = _compAction;
            compDirection = _compDirection;
            compEtherType = _compEtherType;
            compIpNextProtocol = _compIpNextProtocol;
            compSourceIp = _compSourceIp;
            compDestinationIp = _compDestinationIp;
            compSourcePort = _compSourcePort;
            compDestinationPort = _compDestinationPort;
            ToBytes();
        }
        public void ToBytes() {
            ruleBytes =
                compAction.fieldBytes.
                Concat(compDirection.fieldBytes).
                Concat(compEtherType.fieldBytes).
                Concat(compIpNextProtocol.fieldBytes).
                Concat(compSourceIp.fieldBytes).
                Concat(compDestinationIp.fieldBytes).
                Concat(compSourcePort.fieldBytes).
                Concat(compDestinationPort.fieldBytes);

            Console.WriteLine(BitConverter.ToString(ruleBytes.ToArray()));
        }
    }
}
