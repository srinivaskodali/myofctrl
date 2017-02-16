/* Role request and reply message. */
struct ofp_role_request {
	struct ofp_header header; /* Type OFPT_ROLE_REQUEST/OFPT_ROLE_REPLY. */
	uint32_t role; /* One of NX_ROLE_*. */
	uint8_t pad[4]; /* Align to 64 bits. */
	uint64_t generation_id; /* Master Election Generation Id */
};

/* Controller roles. */
enum ofp_controller_role {
		OFPCR_ROLE_NOCHANGE = 0,
		OFPCR_ROLE_EQUAL = 1,
		OFPCR_ROLE_MASTER = 2,
		OFPCR_ROLE_SLAVE = 3,
};

struct ofp_header {
		uint8_t version; /* OFP_VERSION. */
		uint8_t type; /* One of the OFPT_ constants. */
		uint16_t length; /* Length including this ofp_header. */
		uint32_t xid; /* Transaction id associated with this packet.
		   Replies use the same id as was in the request
		   to facilitate pairing. */
};
