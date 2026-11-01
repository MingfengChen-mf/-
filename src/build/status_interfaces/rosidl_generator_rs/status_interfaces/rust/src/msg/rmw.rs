#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "status_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__status_interfaces__msg__Data() -> *const std::ffi::c_void;
}

#[link(name = "status_interfaces__rosidl_generator_c")]
extern "C" {
    fn status_interfaces__msg__Data__init(msg: *mut Data) -> bool;
    fn status_interfaces__msg__Data__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Data>, size: usize) -> bool;
    fn status_interfaces__msg__Data__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Data>);
    fn status_interfaces__msg__Data__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Data>, out_seq: *mut rosidl_runtime_rs::Sequence<Data>) -> bool;
}

// Corresponds to status_interfaces__msg__Data
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Data {
    /// 记录时间戳
    pub stamp: builtin_interfaces::msg::rmw::Time,

    /// 所需三维数组
    pub data_group: [f32; 3],

}



impl Default for Data {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !status_interfaces__msg__Data__init(&mut msg as *mut _) {
        panic!("Call to status_interfaces__msg__Data__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Data {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { status_interfaces__msg__Data__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { status_interfaces__msg__Data__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { status_interfaces__msg__Data__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Data {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Data where Self: Sized {
  const TYPE_NAME: &'static str = "status_interfaces/msg/Data";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__status_interfaces__msg__Data() }
  }
}


