// pages/ctrl/ctrl.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    uid: '326b9e9ceadce1dcc3853668e317ce42',
    topic: "xiaoche",
    main_switch:"on",
    speed_gear: 'Middlespeed',
    forward:'off',
    backward:'off',
    left:'off',
    right:'off',
    stop: 'off',
    bibi: 'off',
    ctrl_click_time: 500,
  },

   //点击总开关
  change_main_switch_status:function(){
    var that = this;
    // 防止连续点击
    if (this.data.mainButtonClicked) {
      wx.showToast({
        title: '休息一下~',
        icon: 'none'
      })
      return
    }
    this.data.mainButtonClicked = true
    setTimeout(() => {
      this.data.mainButtonClicked = false
    }, 3000)  // 可自行修改时间间隔（目前是3秒内只能点击一次按钮）
    if(this.data.main_switch == 'on')
    {
      this.setData({
        main_switch: 'off'
      })
      //控制接口
      wx.request({
        url: 'https://api.bemfa.com/api/device/v1/data/1/', //api接口，详见接入文档
        method:"POST",
        data: {  //请求字段，详见巴法云接入文档，http接口
          uid: that.data.uid,
          topic: that.data.topic,//主题
          msg:"turnoff"   //发送指令
        },
        header: {
          'content-type': "application/x-www-form-urlencoded"
        },
        success (res) {
          console.log("关闭遥控");
          // 跳转回主页
          wx.reLaunch({
            url: '/pages/index/index',
          })
        }
      })
    }
    else
    {
      this.setData({
        main_switch: 'on'
      })
    }
  },

  // 点击前进
  forward_click:function(){
    // 防止连续点击
    if (this.data.ctrlButtonClicked) {
      wx.showToast({
        title: '休息一下~',
        icon: 'none'
      })
      return
    }
    this.data.ctrlButtonClicked = true
    setTimeout(() => {
      this.data.ctrlButtonClicked = false
    }, this.data.ctrl_click_time)  // 可自行修改时间间隔（目前是1秒内只能点击一次按钮）
    var that = this;
    // 图片切换
    if(this.data.forward == 'off' || this.data.backward == 'on'){
      this.setData({
        forward: 'on',
        backward: 'off'
      })
      // 发送前进开指令
      wx.request({
        url: 'https://api.bemfa.com/api/device/v1/data/1/', 
        method:"POST",
        data: {
          uid: that.data.uid,
          topic: that.data.topic,
          msg:"forwardon"
        },
        header: {
          'content-type': "application/x-www-form-urlencoded"
        },
        success (res) {
          console.log("前进开")
        }
      })
    }
    else{
      this.setData({
        forward: 'off'
      })
      // 发送前进关指令
      wx.request({
        url: 'https://api.bemfa.com/api/device/v1/data/1/', 
        method:"POST",
        data: {
          uid: that.data.uid,
          topic: that.data.topic,
          msg:"forwardoff"
        },
        header: {
          'content-type': "application/x-www-form-urlencoded"
        },
        success (res) {
          console.log("前进关")
        }
      })
    }
    
  },

  // 点击后退
  backward_click:function(){
    // 防止连续点击
    if (this.data.mainButtonClicked) {
      wx.showToast({
        title: '休息一下~',
        icon: 'none'
      })
      return
    }
    this.data.mainButtonClicked = true
    setTimeout(() => {
      this.data.mainButtonClicked = false
    }, this.data.ctrl_click_time)  // 可自行修改时间间隔（目前是1秒内只能点击一次按钮）
    var that = this;
    console.log("后退");
    if(this.data.backward == 'off' || this.data.forward == 'on'){
      this.setData({
        backward: 'on',
        forward: 'off'
      })
      // 发送后退开指令
      wx.request({
        url: 'https://api.bemfa.com/api/device/v1/data/1/', 
        method:"POST",
        data: {
          uid: that.data.uid,
          topic: that.data.topic,
          msg:"backwardon"
        },
        header: {
          'content-type': "application/x-www-form-urlencoded"
        },
        success (res) {
          console.log("后退开")
        }
      })
    }
    else{
      this.setData({
        backward: 'off'
      })
      // 发送后退关指令
      wx.request({
        url: 'https://api.bemfa.com/api/device/v1/data/1/', 
        method:"POST",
        data: {
          uid: that.data.uid,
          topic: that.data.topic,
          msg:"backwardoff"
        },
        header: {
          'content-type': "application/x-www-form-urlencoded"
        },
        success (res) {
          console.log("后退关")
        }
      })
    }
  },

  // 长按左向
  left_touchstart:function(){
    var that = this;
    if(this.data.left == 'off' || this.data.right == 'on'){
      this.setData({
        left: 'on',
        right: 'off'
      })
      // 发送左向开指令
      wx.request({
        url: 'https://api.bemfa.com/api/device/v1/data/1/', 
        method:"POST",
        data: {
          uid: that.data.uid,
          topic: that.data.topic,
          msg:"lefton"
        },
        header: {
          'content-type': "application/x-www-form-urlencoded"
        },
        success (res) {
          console.log("左向开")
        }
      })
    }
  },

  // 松开左向
  left_touchend:function(){
    var that=this;
    this.setData({
      left: 'off'
    })
    // 发送左向关指令
    wx.request({
      url: 'https://api.bemfa.com/api/device/v1/data/1/', 
      method:"POST",
      data: {
        uid: that.data.uid,
        topic: that.data.topic,
        msg:"leftoff"
      },
      header: {
        'content-type': "application/x-www-form-urlencoded"
      },
      success (res) {
        console.log("左向关")
      }
    })
  },

  // 长按右向
  right_touchstart:function(){
    var that = this;
    if(this.data.right == 'off' || this.data.left == 'on'){
      this.setData({
        right: 'on',
        left: 'off'
      })
      // 发送右向开指令
      wx.request({
        url: 'https://api.bemfa.com/api/device/v1/data/1/', 
        method:"POST",
        data: {
          uid: that.data.uid,
          topic: that.data.topic,
          msg:"righton"
        },
        header: {
          'content-type': "application/x-www-form-urlencoded"
        },
        success (res) {
          console.log("右向开")
        }
      })
    }
  },

  // 松开右向
  right_touchend:function(){
    var that=this;
    this.setData({
      right: 'off'
    })
    // 发送右向关指令
    wx.request({
      url: 'https://api.bemfa.com/api/device/v1/data/1/', 
      method:"POST",
      data: {
        uid: that.data.uid,
        topic: that.data.topic,
        msg:"rightoff"
      },
      header: {
        'content-type': "application/x-www-form-urlencoded"
      },
      success (res) {
        console.log("右向关")
      }
    })
  },

  // 点击右向
  right_click:function(){
    // 防止连续点击
    if (this.data.mainButtonClicked) {
      wx.showToast({
        title: '休息一下~',
        icon: 'none'
      })
      return
    }
    this.data.mainButtonClicked = true
    setTimeout(() => {
      this.data.mainButtonClicked = false
    }, this.data.click_time)  // 可自行修改时间间隔（目前是1秒内只能点击一次按钮）
    var that = this;
    console.log("右向");
    if(this.data.right == 'off' || this.data.left == 'on'){
      this.setData({
        right: 'on',
        left: 'off'
      })
      // 发送右向开指令
      wx.request({
        url: 'https://api.bemfa.com/api/device/v1/data/1/', 
        method:"POST",
        data: {
          uid: that.data.uid,
          topic: that.data.topic,
          msg:"righton"
        },
        header: {
          'content-type': "application/x-www-form-urlencoded"
        },
        success (res) {
          console.log("右向开")
        }
      })
    }
    else{
      this.setData({
        right: 'off'
      })
      // 发送右向关指令
      wx.request({
        url: 'https://api.bemfa.com/api/device/v1/data/1/', 
        method:"POST",
        data: {
          uid: that.data.uid,
          topic: that.data.topic,
          msg:"rightoff"
        },
        header: {
          'content-type': "application/x-www-form-urlencoded"
        },
        success (res) {
          console.log("右向关")
        }
      })
    }
  },

  // 长按刹车
  stop_touchstart:function(){
    var that = this;
    if(this.data.stop == 'off'){
      this.setData({
        forward: 'off',
        backward: 'off',
        left: 'off',
        right: 'off',
        stop: 'on'
      })
      // 发送急刹指令
      wx.request({
        url: 'https://api.bemfa.com/api/device/v1/data/1/', 
        method:"POST",
        data: {
          uid: that.data.uid,
          topic: that.data.topic,
          msg:"allstop"
        },
        header: {
          'content-type': "application/x-www-form-urlencoded"
        },
        success (res) {
          console.log("急刹");
        }
      })
    }
  },

  // 松开刹车
  stop_touch_end:function(){
    this.setData({
      stop: 'off'
    })
  },

  // 点击喇叭
  bibi_click:function(){
    var that=this;
    if (this.data.bibiButtonClicked) {
      wx.showToast({
        title: '休息一下~',
        icon: 'none'
      })
      return
    }
    this.data.bibiButtonClicked = true
    setTimeout(() => {
      this.data.bibiButtonClicked = false
    }, 3000)  // 可自行修改时间间隔（目前是3秒内只能点击一次按钮）
      // 发送点击指令
      wx.request({
        url: 'https://api.bemfa.com/api/device/v1/data/1/', 
        method:"POST",
        data: {
          uid: that.data.uid,
          topic: that.data.topic,
          msg:"bibi"
        },
        header: {
          'content-type': "application/x-www-form-urlencoded"
        },
        success (res) {
          console.log("喇叭响");
        }
      })
  },

  // 调速
  change_speed_gear:function(){
    var that=this;
    if (this.data.speedButtonClicked) {
      wx.showToast({
        title: '休息一下~',
        icon: 'none'
      })
      return
    }
    this.data.speedButtonClicked = true
    setTimeout(() => {
      this.data.speedButtonClicked = false
    }, 3000)  // 可自行修改时间间隔（目前是3秒内只能点击一次按钮）

    if(this.data.speed_gear == 'Middlespeed'){
      this.setData({
        speed_gear: 'Highspeed'
      })
      // 发送调速指令
      wx.request({
        url: 'https://api.bemfa.com/api/device/v1/data/1/', 
        method:"POST",
        data: {
          uid: that.data.uid,
          topic: that.data.topic,
          msg:"highspeed"
        },
        header: {
          'content-type': "application/x-www-form-urlencoded"
        },
        success (res) {
          console.log("切换高速");
        }
      })
    }
    else{
      this.setData({
        speed_gear: 'Middlespeed'
      })
      // 发送调速指令
      wx.request({
        url: 'https://api.bemfa.com/api/device/v1/data/1/', 
        method:"POST",
        data: {
          uid: that.data.uid,
          topic: that.data.topic,
          msg:"middlespeed"
        },
        header: {
          'content-type': "application/x-www-form-urlencoded"
        },
        success (res) {
          console.log("切换中速");
        }
      })
    }
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {

  },
})