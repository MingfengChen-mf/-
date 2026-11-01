#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to status_interfaces__msg__Data

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Data {
    /// 记录时间戳
    pub stamp: builtin_interfaces::msg::Time,

    /// 所需三维数组
    pub data_group: [f32; 3],

}



impl Default for Data {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Data::default())
  }
}

impl rosidl_runtime_rs::Message for Data {
  type RmwMsg = super::msg::rmw::Data;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
        data_group: msg.data_group,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
        data_group: msg.data_group,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
      data_group: msg.data_group,
    }
  }
}


