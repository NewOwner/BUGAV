typedef struct _PASSTHROUGH_DATA {

    //  The object that identifies this driver.
    PDRIVER_OBJECT DriverObject;

    //  The filter that results from a call to
    //  FltRegisterFilter.
    PFLT_FILTER Filter;

    //  Server port: user mode connects to this port
    PFLT_PORT ServerPort;

    //  Client connection port: only one connection is allowed at a time.,
    PFLT_PORT ClientPort;

} PASSTHROUGH_DATA, * PPASSTHROUGH_DATA;


typedef enum _PASSTHROUGH_COMMAND {
    UpdateConfig

} PASSTHROUGH_COMMAND;

//
//  Defines the command structure between the utility and the filter.
#pragma warning(push)
#pragma warning(disable:4200) // disable warnings for structures with zero length arrays.

typedef struct _COMMAND_MESSAGE {
    PASSTHROUGH_COMMAND Command;
    ULONG Reserved;  // Alignment on IA64
    UCHAR Data[];
} COMMAND_MESSAGE, * PCOMMAND_MESSAGE;

#pragma warning(pop)
