#include "TcpSegment.h"
#include "TcpConnection.h"
#include "TcpConnection_sm.h"
using namespace statemap;
// FSM Map constructor.
TCP::TCP() :
	CLOSED("CLOSED", 0),
	CLOSE_WAIT("CLOSE_WAIT", 1),
	CLOSING("CLOSING", 2),
	ClientOpening("ClientOpening", 3),
	Default("Default", 4),
	ESTABLISHED("ESTABLISHED", 5),
	FIN_WAIT_1("FIN_WAIT_1", 6),
	FIN_WAIT_2("FIN_WAIT_2", 7),
	LAST_ACK("LAST_ACK", 8),
	LISTEN("LISTEN", 9),
	SYN_RCVD("SYN_RCVD", 10),
	SYN_SENT("SYN_SENT", 11),
	ServiceOpening("ServiceOpening", 12),
	TIME_WAIT("TIME_WAIT", 13),
	Transmitting("Transmitting", 14)
{}

// Class state -----------------------------------
void TcpConnectionState::ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
     Default(context);
}
void TcpConnectionState::AcceptOpen(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
     Default(context);
}
void TcpConnectionState::AckTimeout(TcpConnectionContext<TcpConnection>& context) {
     Default(context);
}
void TcpConnectionState::ActiveOpen(TcpConnectionContext<TcpConnection>& context, const SocketAddress* address) {
     Default(context);
}
void TcpConnectionState::ClientOpened(TcpConnectionContext<TcpConnection>& context, const SocketAddress* address) {
     Default(context);
}
void TcpConnectionState::Close(TcpConnectionContext<TcpConnection>& context) {
     Default(context);
}
void TcpConnectionState::CloseAckTimeout(TcpConnectionContext<TcpConnection>& context) {
     Default(context);
}
void TcpConnectionState::CloseTimeout(TcpConnectionContext<TcpConnection>& context) {
     Default(context);
}
void TcpConnectionState::ConnAckTimeout(TcpConnectionContext<TcpConnection>& context) {
     Default(context);
}
void TcpConnectionState::FIN(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
     Default(context);
}
void TcpConnectionState::FIN_ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
     Default(context);
}
void TcpConnectionState::OpenFailed(TcpConnectionContext<TcpConnection>& context, const char* reason) {
     Default(context);
}
void TcpConnectionState::PSH(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
     Default(context);
}
void TcpConnectionState::PSH_ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
     Default(context);
}
void TcpConnectionState::PassiveOpen(TcpConnectionContext<TcpConnection>& context, unsigned short port) {
     Default(context);
}
void TcpConnectionState::RST(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
     Default(context);
}
void TcpConnectionState::RST_ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
     Default(context);
}
void TcpConnectionState::SYN(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
     Default(context);
}
void TcpConnectionState::SYN_ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
     Default(context);
}
void TcpConnectionState::ServerOpened(TcpConnectionContext<TcpConnection>& context) {
     Default(context);
}
void TcpConnectionState::TransAckTimeout(TcpConnectionContext<TcpConnection>& context) {
     Default(context);
}
void TcpConnectionState::Transmit(TcpConnectionContext<TcpConnection>& context, const char* data, int offset, int size) {
     Default(context);
}
void TcpConnectionState::UNDEF(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
     Default(context);
}
void TcpConnectionState::URG(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
     Default(context);
}
// FSM map default state class.-------------------
void TcpConnectionState::Default(TcpConnectionContext<TcpConnection>& context) {
    throw TransitionUndefinedException(context.getState().getName(), context.getTransition());
    return;
}

// ----------------------------------------------------
void TCP_CLOSED::PassiveOpen(TcpConnectionContext<TcpConnection>& context, unsigned short port) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.openServerSocket(port );
			context.setState(context.ServiceOpening);
		} catch (...) {
			context.setState(context.ServiceOpening);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_CLOSED::ActiveOpen(TcpConnectionContext<TcpConnection>& context, const SocketAddress* address) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.openClientSocket(address );
			context.setState(context.ClientOpening);
		} catch (...) {
			context.setState(context.ClientOpening);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_CLOSED::AcceptOpen(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.sendSynAck(segment );
			ctxt.setNearAddress();
			context.setState(context.SYN_RCVD);
		} catch (...) {
			context.setState(context.SYN_RCVD);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_CLOSED::Close(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_CLOSE_WAIT::Close(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: FIN , NULL , 0 , 0 , NULL );
			context.setState(context.LAST_ACK);
		} catch (...) {
			context.setState(context.LAST_ACK);
			throw;
		}
		context.getState().Entry(context);
	} 
}
void TCP_CLOSING::Entry(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.startTimer("CLOSE_ACK_TIMER" , TcpConnection :: ACK_TIMEOUT );
}
void TCP_CLOSING::Exit(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.stopTimer("CLOSE_ACK_TIMER" );
}

// ----------------------------------------------------
void TCP_CLOSING::ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if ((((segment.getSrcAddress() == ctxt.getFarAddress()) && (segment.getSrcPort() == ctxt.getFarPort())) && (segment.getAcknowledgeNumber() == ctxt.getSequenceNumber()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.deleteSegment(segment );
			context.setState(context.TIME_WAIT);
		} catch (...) {
			context.setState(context.TIME_WAIT);
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		TCP_Default::ACK(context, segment);
	}
}

// ----------------------------------------------------
void TCP_CLOSING::CloseAckTimeout(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.closeSocket();
			ctxt.closed("" );
			context.setState(context.TIME_WAIT);
		} catch (...) {
			context.setState(context.TIME_WAIT);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_CLOSING::UNDEF(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_ClientOpening::ClientOpened(TcpConnectionContext<TcpConnection>& context, const SocketAddress* address) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.sendOpenSyn(address );
			context.setState(context.SYN_SENT);
		} catch (...) {
			context.setState(context.SYN_SENT);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_ClientOpening::OpenFailed(TcpConnectionContext<TcpConnection>& context, const char* reason) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.closeSocket();
			ctxt.openFailed(reason );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::PassiveOpen(TcpConnectionContext<TcpConnection>& context, unsigned short port) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.openFailed("already open" );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::ActiveOpen(TcpConnectionContext<TcpConnection>& context, const SocketAddress* address) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.openFailed("already open" );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::Transmit(TcpConnectionContext<TcpConnection>& context, const char* data, int offset, int size) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.transmitFailed("connection not established" );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::FIN(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (((segment.getSrcAddress() != ctxt.getFarAddress()) || (segment.getSrcPort() != ctxt.getFarPort()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::SYN(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (((segment.getSrcAddress() != ctxt.getFarAddress()) || (segment.getSrcPort() != ctxt.getFarPort()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::PSH(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (((segment.getSrcAddress() != ctxt.getFarAddress()) || (segment.getSrcPort() != ctxt.getFarPort()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (((segment.getSrcAddress() != ctxt.getFarAddress()) || (segment.getSrcPort() != ctxt.getFarPort()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::URG(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (((segment.getSrcAddress() != ctxt.getFarAddress()) || (segment.getSrcPort() != ctxt.getFarPort()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::FIN_ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (((segment.getSrcAddress() != ctxt.getFarAddress()) || (segment.getSrcPort() != ctxt.getFarPort()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::SYN_ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (((segment.getSrcAddress() != ctxt.getFarAddress()) || (segment.getSrcPort() != ctxt.getFarPort()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::PSH_ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (((segment.getSrcAddress() != ctxt.getFarAddress()) || (segment.getSrcPort() != ctxt.getFarPort()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::UNDEF(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (((segment.getSrcAddress() != ctxt.getFarAddress()) || (segment.getSrcPort() != ctxt.getFarPort()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.closed("connection reset" );
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::RST(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.closed("connection reset by peer" );
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::RST_ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.closed("connection reset by peer" );
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::ConnAckTimeout(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::TransAckTimeout(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::CloseAckTimeout(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Default::CloseTimeout(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_ESTABLISHED::FIN(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (((segment.getSrcAddress() == ctxt.getFarAddress()) && (segment.getSrcPort() == ctxt.getFarPort()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: ACK , NULL , 0 , 0 , & segment );
			ctxt.halfClosed();
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSE_WAIT);
		} catch (...) {
			context.setState(context.CLOSE_WAIT);
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		TCP_Default::FIN(context, segment);
	}
}

// ----------------------------------------------------
void TCP_ESTABLISHED::PSH(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (((segment.getSrcAddress() == ctxt.getFarAddress()) && (segment.getSrcPort() == ctxt.getFarPort()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: ACK , NULL , 0 , 0 , & segment );
			ctxt.receive(segment );
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		TCP_Default::PSH(context, segment);
	}
}

// ----------------------------------------------------
void TCP_ESTABLISHED::Transmit(TcpConnectionContext<TcpConnection>& context, const char* data, int offset, int size) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: PSH , data , offset , size , NULL );
			context.setState(context.Transmitting);
		} catch (...) {
			context.setState(context.Transmitting);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_ESTABLISHED::Close(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: FIN , NULL , 0 , 0 , NULL );
			context.setState(context.FIN_WAIT_1);
		} catch (...) {
			context.setState(context.FIN_WAIT_1);
			throw;
		}
		context.getState().Entry(context);
	} 
}
void TCP_FIN_WAIT_1::Entry(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.startTimer("CLOSE_ACK_TIMER" , TcpConnection :: ACK_TIMEOUT );
}
void TCP_FIN_WAIT_1::Exit(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.stopTimer("CLOSE_ACK_TIMER" );
}

// ----------------------------------------------------
void TCP_FIN_WAIT_1::ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if ((((segment.getSrcAddress() == ctxt.getFarAddress()) && (segment.getSrcPort() == ctxt.getFarPort())) && (segment.getAcknowledgeNumber() == ctxt.getSequenceNumber()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.deleteSegment(segment );
			context.setState(context.FIN_WAIT_2);
		} catch (...) {
			context.setState(context.FIN_WAIT_2);
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		TCP_Default::ACK(context, segment);
	}
}

// ----------------------------------------------------
void TCP_FIN_WAIT_1::FIN(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (((segment.getSrcAddress() == ctxt.getFarAddress()) && (segment.getSrcPort() == ctxt.getFarPort()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: ACK , NULL , 0 , 0 , & segment );
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSING);
		} catch (...) {
			context.setState(context.CLOSING);
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		TCP_Default::FIN(context, segment);
	}
}

// ----------------------------------------------------
void TCP_FIN_WAIT_1::FIN_ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if ((((segment.getSrcAddress() == ctxt.getFarAddress()) && (segment.getSrcPort() == ctxt.getFarPort())) && (segment.getAcknowledgeNumber() == ctxt.getSequenceNumber()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: ACK , NULL , 0 , 0 , & segment );
			ctxt.deleteSegment(segment );
			context.setState(context.TIME_WAIT);
		} catch (...) {
			context.setState(context.TIME_WAIT);
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		TCP_Default::FIN_ACK(context, segment);
	}
}

// ----------------------------------------------------
void TCP_FIN_WAIT_1::CloseAckTimeout(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.closeSocket();
			ctxt.closed("" );
			context.setState(context.FIN_WAIT_2);
		} catch (...) {
			context.setState(context.FIN_WAIT_2);
			throw;
		}
		context.getState().Entry(context);
	} 
}
void TCP_FIN_WAIT_2::Entry(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.startTimer("CLOSE_ACK_TIMER" , TcpConnection :: ACK_TIMEOUT );
}
void TCP_FIN_WAIT_2::Exit(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.stopTimer("CLOSE_ACK_TIMER" );
}

// ----------------------------------------------------
void TCP_FIN_WAIT_2::FIN(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (((segment.getSrcAddress() == ctxt.getFarAddress()) && (segment.getSrcPort() == ctxt.getFarPort()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: ACK , NULL , 0 , 0 , & segment );
			ctxt.deleteSegment(segment );
			context.setState(context.TIME_WAIT);
		} catch (...) {
			context.setState(context.TIME_WAIT);
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		TCP_Default::FIN(context, segment);
	}
}

// ----------------------------------------------------
void TCP_FIN_WAIT_2::CloseAckTimeout(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.closeSocket();
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_FIN_WAIT_2::UNDEF(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} 
}
void TCP_LAST_ACK::Entry(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.startTimer("CLOSE_ACK_TIMER" , TcpConnection :: ACK_TIMEOUT );
}
void TCP_LAST_ACK::Exit(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.stopTimer("CLOSE_ACK_TIMER" );
}

// ----------------------------------------------------
void TCP_LAST_ACK::ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if ((((segment.getSrcAddress() == ctxt.getFarAddress()) && (segment.getSrcPort() == ctxt.getFarPort())) && (segment.getAcknowledgeNumber() == ctxt.getSequenceNumber()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: FIN , NULL , 0 , 0 , & segment );
			ctxt.closeSocket();
			ctxt.closed("" );
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		TCP_Default::ACK(context, segment);
	}
}

// ----------------------------------------------------
void TCP_LAST_ACK::CloseAckTimeout(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.closeSocket();
			ctxt.closed("" );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_LISTEN::SYN(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.accept(segment );
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_LISTEN::Close(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.closeSocket();
			ctxt.closed("" );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_LISTEN::RST(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_LISTEN::UNDEF(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , & segment );
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} 
}
void TCP_SYN_RCVD::Entry(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.startTimer("ACK_TIMER" , TcpConnection :: ACK_TIMEOUT );
}
void TCP_SYN_RCVD::Exit(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.stopTimer("ACK_TIMER" );
}

// ----------------------------------------------------
void TCP_SYN_RCVD::RST(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.closeSocket();
			ctxt.clearListener();
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_SYN_RCVD::ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if ((((segment.getSrcAddress() == ctxt.getFarAddress()) && (segment.getSrcPort() == ctxt.getFarPort())) && (segment.getAcknowledgeNumber() == ctxt.getSequenceNumber()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.accepted();
			ctxt.deleteSegment(segment );
			context.setState(context.ESTABLISHED);
		} catch (...) {
			context.setState(context.ESTABLISHED);
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		TCP_Default::ACK(context, segment);
	}
}

// ----------------------------------------------------
void TCP_SYN_RCVD::Close(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: FIN , NULL , 0 , 0 , NULL );
			context.setState(context.FIN_WAIT_1);
		} catch (...) {
			context.setState(context.FIN_WAIT_1);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_SYN_RCVD::AckTimeout(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: RST , NULL , 0 , 0 , NULL );
			ctxt.closeSocket();
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}
void TCP_SYN_SENT::Entry(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.startTimer("CONN_ACK_TIMER" , TcpConnection :: ACK_TIMEOUT );
}
void TCP_SYN_SENT::Exit(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.stopTimer("CONN_ACK_TIMER" );
}

// ----------------------------------------------------
void TCP_SYN_SENT::SYN_ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if ((((segment.getSrcAddress() == ctxt.getFarAddress()) && (segment.getSrcPort() == ctxt.getFarPort())) && (segment.getAcknowledgeNumber() == ctxt.getSequenceNumber()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.setFarAddress(segment );
			ctxt.sendSynAckAck(segment );
			ctxt.openSuccess();
			ctxt.deleteSegment(segment );
			context.setState(context.ESTABLISHED);
		} catch (...) {
			context.setState(context.ESTABLISHED);
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		TCP_Default::SYN_ACK(context, segment);
	}
}

// ----------------------------------------------------
void TCP_SYN_SENT::Close(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.closeSocket();
			ctxt.closed("" );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_SYN_SENT::ConnAckTimeout(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.closeSocket();
			ctxt.openFailed("acknowledge timeout" );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_ServiceOpening::ServerOpened(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.openSuccess();
			context.setState(context.LISTEN);
		} catch (...) {
			context.setState(context.LISTEN);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_ServiceOpening::OpenFailed(TcpConnectionContext<TcpConnection>& context, const char* reason) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.closeSocket();
			ctxt.openFailed(reason );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}
void TCP_TIME_WAIT::Entry(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.startTimer("CLOSE_TIMER" , TcpConnection :: CLOSE_TIMEOUT );
}
void TCP_TIME_WAIT::Exit(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.stopTimer("CLOSE_TIMER" );
}

// ----------------------------------------------------
void TCP_TIME_WAIT::FIN_ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if ((((segment.getSrcAddress() == ctxt.getFarAddress()) && (segment.getSrcPort() == ctxt.getFarPort())) && (segment.getAcknowledgeNumber() == ctxt.getSequenceNumber()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.closeSocket();
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		TCP_Default::FIN_ACK(context, segment);
	}
}

// ----------------------------------------------------
void TCP_TIME_WAIT::CloseTimeout(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.closeSocket();
			ctxt.closed("" );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_TIME_WAIT::UNDEF(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} 
}
void TCP_Transmitting::Entry(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.startTimer("TRANS_ACK_TIMER" , TcpConnection :: ACK_TIMEOUT );
}
void TCP_Transmitting::Exit(TcpConnectionContext<TcpConnection>& context) {
    TcpConnection& ctxt = context.getOwner();
	ctxt.stopTimer("TRANS_ACK_TIMER" );
}

// ----------------------------------------------------
void TCP_Transmitting::ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if ((((segment.getSrcAddress() == ctxt.getFarAddress()) && (segment.getSrcPort() == ctxt.getFarPort())) && (segment.getAcknowledgeNumber() == ctxt.getSequenceNumber()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.transmitted();
			ctxt.deleteSegment(segment );
			context.setState(context.ESTABLISHED);
		} catch (...) {
			context.setState(context.ESTABLISHED);
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		TCP_Default::ACK(context, segment);
	}
}

// ----------------------------------------------------
void TCP_Transmitting::PSH_ACK(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if ((((segment.getSrcAddress() == ctxt.getFarAddress()) && (segment.getSrcPort() == ctxt.getFarPort())) && (segment.getAcknowledgeNumber() == ctxt.getSequenceNumber()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: ACK , NULL , 0 , 0 , & segment );
			ctxt.transmitted();
			ctxt.receive(segment );
			ctxt.deleteSegment(segment );
			context.setState(context.ESTABLISHED);
		} catch (...) {
			context.setState(context.ESTABLISHED);
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		TCP_Default::PSH_ACK(context, segment);
	}
}

// ----------------------------------------------------
void TCP_Transmitting::PSH(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (((segment.getSrcAddress() == ctxt.getFarAddress()) && (segment.getSrcPort() == ctxt.getFarPort()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: ACK , NULL , 0 , 0 , & segment );
			ctxt.receive(segment );
			ctxt.deleteSegment(segment );
		} catch (...) {
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		TCP_Default::PSH(context, segment);
	}
}

// ----------------------------------------------------
void TCP_Transmitting::FIN(TcpConnectionContext<TcpConnection>& context, const TcpSegment& segment) {
	TcpConnection& ctxt = context.getOwner();
	
	if (((segment.getSrcAddress() == ctxt.getFarAddress()) && (segment.getSrcPort() == ctxt.getFarPort()))) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: ACK , NULL , 0 , 0 , & segment );
			ctxt.halfClosed();
			ctxt.deleteSegment(segment );
			context.setState(context.CLOSE_WAIT);
		} catch (...) {
			context.setState(context.CLOSE_WAIT);
			throw;
		}
		context.getState().Entry(context);
	} else 
	if (true) {
		TCP_Default::FIN(context, segment);
	}
}

// ----------------------------------------------------
void TCP_Transmitting::Close(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.doSend(TcpSegment :: FIN , NULL , 0 , 0 , NULL );
			context.setState(context.FIN_WAIT_1);
		} catch (...) {
			context.setState(context.FIN_WAIT_1);
			throw;
		}
		context.getState().Entry(context);
	} 
}

// ----------------------------------------------------
void TCP_Transmitting::TransAckTimeout(TcpConnectionContext<TcpConnection>& context) {
	TcpConnection& ctxt = context.getOwner();
	
	if (true) {
		context.getState().Exit(context);
		context.clearState();
		try {
			ctxt.transmitFailed("peer did not acknowledge" );
			ctxt.closed("connection lost" );
			context.setState(context.CLOSED);
		} catch (...) {
			context.setState(context.CLOSED);
			throw;
		}
		context.getState().Entry(context);
	} 
}
