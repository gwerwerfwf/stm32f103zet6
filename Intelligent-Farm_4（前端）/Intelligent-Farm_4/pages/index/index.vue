<template>
	<view class="wrapper">
		<!--数据部分-->
		<view class="device-area">
			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">设备号</view>
					<image class="device-logo" src="/static/Id.png"></image>
				</view>
				<view class="device-data">{{deviceId}}</view>
			</view>
			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">温度1</view>
					<image class="device-logo" src="/static/Temp.png"></image>
				</view>
				<view class="device-data">{{temp}}℃</view>
			</view>
			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">温度2</view>
					<image class="device-logo" src="/static/Temp2.png"></image>
				</view>
				<view class="device-data">{{temp1}}℃</view>
			</view>
			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">湿度</view>
					<image class="device-logo" src="/static/Humi.png"></image>
				</view>
				<view class="device-data">{{humi}}%</view>
			</view>
			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">光照度</view>
					<image class="device-logo" src="/static/Light.png"></image>
				</view>
				<view class="device-data">{{ld}}Lx</view>
			</view>
			<!-- <view class="device-cart">
				<view class="device-info">
					<view class="device-name">故障状态</view>
					<image class="device-logo" src="/static/Status.png"></image>
				</view>
				<view class="device-data">{{status}}</view>
			</view>
			 -->
			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">照明</view>
					<image class="device-logo" src="/static/Light1.png"></image>
				</view>
				<view class="device-data">{{ light === 1 ? '开启' : (light === 0 ? '关闭' : light) }}</view>
				<!-- <view class="device-data" :class="light === 1 ? '开启' : '关闭'">{{ light }}</view> -->
				<!-- <view class="device-data"></view> -->
			</view>

			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">通风</view>
					<image class="device-logo" src="/static/Vent.png"></image>
				</view>
				<!-- <view class="device-data" :class="vent ===1 ? '开启' : '关闭'">{{ vent }}</view> -->
				<view class="device-data">{{ vent === 1 ? '开启' : (vent === 0 ? '关闭' : vent) }}</view>
			</view>

			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">滴灌</view>
					<image class="device-logo" src="/static/irr1.png"></image>
				</view>
				<view class="device-data">{{ irr === 1 ? '开启' : (irr === 0 ? '关闭' : irr) }}</view>
				<!-- <view class="device-data" :class="irr === 1 ? '开启' : '关闭'">{{ irr }}</view> -->
			</view>

			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">非法闯入</view>
					<image class="device-logo" src="/static/rush.png"></image>
				</view>
				<!-- <view class="device-data" :class="rush === 1 ? '开启' : '关闭'">{{ rush }}</view> -->
				<view class="device-data">{{ rush === 1 ? '是' : (rush === 0 ? '否' : rush) }}</view>
			</view>

			<view class="device-cart-no">
				<p>时间</p>
				<view class="device-info">
					<view class="device-name"></view>
					<image class="device-logo" src=""></image>
				</view>
				<view class="device-data"></view>
			</view>

		</view>
		<br>
		<!--设备2-->
		<view class="device-area">
			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">设备号</view>
					<image class="device-logo" src="/static/Id.png"></image>
				</view>
				<view class="device-data">{{ deviceId2 }}</view>
			</view>

			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">温度1</view>
					<image class="device-logo" src="/static/Temp.png"></image>
				</view>
				<view class="device-data">{{ temp2 }}℃</view>
			</view>
			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">温度2</view>
					<image class="device-logo" src="/static/Temp2.png"></image>
				</view>
				<view class="device-data">{{ temp3 }}℃</view>
			</view>

			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">湿度</view>
					<image class="device-logo" src="/static/Humi.png"></image>
				</view>
				<view class="device-data">{{ humi2 }}%</view>
			</view>

			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">光照度</view>
					<image class="device-logo" src="/static/Light.png"></image>
				</view>
				<view class="device-data">{{ ld2 }}Lx</view>
			</view>
			<!-- <view class="device-cart">
				<view class="device-info">
					<view class="device-name">故障状态</view>
					<image class="device-logo" src="/static/Status.png"></image>
				</view>
				<view class="device-data">{{ status2 }}</view>
			</view> -->

			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">照明</view>
					<image class="device-logo" src="/static/Light1.png"></image>
				</view>
				<!-- <view class="device-data" :class="light2 === 1 ? '开启' : '关闭'">{{ light2 }}</view> -->
				<view class="device-data">{{ light2 === 1 ? '开启' : (light2 === 0 ? '关闭' : light2) }}</view>
			</view>

			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">通风</view>
					<image class="device-logo" src="/static/Vent.png"></image>
				</view>
				<!-- <view class="device-data" :class="vent2 === 1 ? '开启' : '关闭'">{{ vent2 }}</view> -->
				<view class="device-data">{{ vent2 === 1 ? '开启' : (vent2 === 0 ? '关闭' : vent2) }}</view>
			</view>

			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">滴灌</view>
					<image class="device-logo" src="/static/irr1.png"></image>
				</view>
				<!-- <view class="device-data" :class="irr2 === 1 ? '开启' : '关闭'">{{ irr2 }}</view> -->
				<view class="device-data">{{ irr2 === 1 ? '开启' : (irr2 === 0 ? '关闭' : irr2) }}</view>
			</view>

			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">非法闯入</view>
					<image class="device-logo" src="/static/rush.png"></image>
				</view>
			<!-- 	<view class="device-data" :class="rush2 === 1 ? '开启' : '关闭'">{{ rush2 }}</view> -->
			<view class="device-data">{{ rush2 === 1 ? '是' : (rush2 === 0 ? '否' : rush2) }}</view>
			</view>

			<view class="device-cart-no">
				<p>时间</p>
				<view class="device-info">
					<view class="device-name"></view>
					<image class="device-logo" src=""></image>
				</view>
				<view class="device-data"></view>
			</view>


		</view>
	</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				id: null,
				humi: null,
				temp: null,
				temp1: null,
				ld: null,
				status: null,
				deviceId: null,
				light: null,
				vent: null,
				irr: null,
				rush: null,


				id2: null,
				humi2: null,
				temp2: null,
				temp3: null,
				ld2: null,
				status2: null,
				deviceId2: null,
				light2: null,
				vent2: null,
				irr2: null,
				rush2: null,
			}
		},

		onShow() {
			let that = this
			this.GetDatapoints()
			setInterval(function() {
				that.GetDatapoints()
			}, 3000);
		},

		methods: {

			GetDatapoints: function() {
				uni.request({
					url: 'http://10.152.132.235:9999/greenhouse/queryAll',
					header: {

					},
					method: 'GET',
					success: (res) => {
						//  console.log('接口返回------',res.data);
						// this.id = res.data.data.greenHouse[0].id;
						// this.temp = res.data.data.greenHouse[0].temp;
						// this.humi= res.data.data.greenHouse[0].humi;
						// this.ld =res.data.data.greenHouse[0].ld;
						// this.status =res.data.data.greenHouse[0].status;
						console.log('接口返回------', res.data);
						const greenHouseData = res.data.data.greenHouse;
						if (Array.isArray(greenHouseData) && greenHouseData.length > 0) {
							//const latestData = greenHouseData[greenHouseData.length - 1];
							const latestData = greenHouseData.filter((item) => item.deviceId === 1)[
								greenHouseData.filter((item) => item.deviceId === 1).length - 1];
							this.id = latestData.id;
							this.temp = latestData.temp1;
							this.temp1 = latestData.temp2;
							this.humi = latestData.humi;
							this.ld = latestData.ld;
							//this.status = latestData.status;
							this.deviceId = latestData.deviceId;
							this.light = latestData.light;
							this.vent = latestData.vent;
							this.irr = latestData.irr;
							this.rush = latestData.rush;



							// 获取第二个设备的最新数据
							const secondLatestData = greenHouseData.filter((item) => item.deviceId === 2)[
								greenHouseData.filter((item) => item.deviceId === 2).length - 1];
							this.id2 = secondLatestData.id;
							this.temp2 = secondLatestData.temp1;
							this.temp3 = secondLatestData.temp2;
							this.humi2 = secondLatestData.humi;
							this.ld2 = secondLatestData.ld;
							//this.status2 = secondLatestData.status;
							this.deviceId2 = secondLatestData.deviceId;
							this.light2 = secondLatestData.light;
							this.vent2 = secondLatestData.vent;
							this.irr2 = secondLatestData.irr;
							this.rush2 = secondLatestData.rush;

						}
					},
				});
			},

		}
	}
</script>

<style>
	.wrapper {
		padding: 32rpx;
	}

	.device-area {
		display: flex;
		justify-content: space-between;
		flex-wrap: wrap;
	}

	.device-cart {
		width: 200rpx;
		height: 128rpx;
		border-radius: 30rpx;
		margin-top: 30rpx;
		display: flex;
		justify-content: space-around;
		align-items: center;
		/* background-color: #8f8f94; */
		box-shadow: 0 0 15rpx #ccc;
	}

	.device-cart-no {
		/* width: 320rpx; */
		width: 800rpx;
		height: 99rpx;
		border-radius: 30rpx;
		margin-top: 30rpx;
		display: flex;
		justify-content: space-around;
		align-items: center;
		/* background-color: #8f8f94; */
		box-shadow: 0 0 15rpx #ccc;
	}

	.device-info {
		font-size: 20rpx;
		/* background-color: #8f8f94; */
	}

	.device-name {
		text-align: center;
		color: #6d6d6d;
	}

	.device-logo {
		width: 70rpx;
		height: 70rpx;
		margin-top: 10rpx;
	}

	.device-data {
		font-size: 50rpx;
		color: #6d6d6d;

	}

	.header-container {
		background-color: #3d7ef9;
		color: #fff;
		border-radius: 36rpx;
		padding: 36rpx 68rpx;
	}

	.header-air {
		display: flex;
		justify-content: space-between;
		font-size: 32rpx;
	}

	.header-title {
		display: flex;
		justify-content: space-between;
		font-size: 64rpx;
	}

	.header-ad {
		margin: top 24rpx;
		;
		display: flex;
		justify-content: space-between;
		font-size: 28rpx;
	}
</style>