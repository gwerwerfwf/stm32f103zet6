<!-- <template>
	<view class="wrapper">
		<label for="deviceSelect">选择设备：</label>
		<select id="deviceSelect" v-model="selectedDevice" class="custom-select" @change="handleDeviceChange">
		  <option value="">请选择设备</option>
		  <option value="1">设备1</option>
		  <option value="0">设备2</option>
		</select>
		<br>
		<br>
		<view class="device-area">
			
			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">LED灯</view>
					<image class="device-logo" src="/static/Led.png"></image>
				</view>
				<switch @change="onLedSwitch" color="#2b9939" :checked="ldstatus"/>
			</view>
			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">风扇1</view>
					<image class="device-logo" src="/static/Fan.png"></image>
				</view>
				<switch @change="onFanSwitch01" color="#2b9939" :checked="motor1"/>
			</view>
			
			<view class="device-cart">
				<view class="device-info">
					<view class="device-name">风扇2</view>
					<image class="device-logo" src="/static/Fan.png"></image>
				</view>
				<switch @change="onFanSwitch02" color="#2b9939" :checked="motor2"/>
			</view>
		</view>
		
		<br>

		<view>
		    <button @click="Switch">点击跳转</button>
		  </view>
	</view>
</template>

<script>
	import { http } from '../../utils/http';
	export default {
		data() {
			return {
				ldstatus:false,
				motor1:false,
				motor2:false,
				swi:false,
				selectedDevice:'',
			}
		},
		
		
		 	onLoad() {
			
		 },
		methods: {
		handleDeviceChange(event){
			let deviceId = '';
			       if (this.selectedDevice === '1') {
			         deviceId = '1';
			       } else if (this.selectedDevice === '0') {
			         deviceId = '0';
					}	
			return deviceId;
		},
			onLedSwitch(event) {
				console.log(event.detail.value);
				let sw = event.detail.value;
				 const deviceId = this.handleDeviceChange();
				if(sw) {
					
					http({
						method:'GET',
						url: '/greenhouse/updateData',//后端接口地址
						data: {
							ldstatus:1,	
							 deviceId :deviceId,
							
						},
					}).then((res)=>{
						console.log('LED on!')
					})   
				
				}
				else {
					http({
						method:'GET',
						url: '/greenhouse/updateData',//后端接口地址
						data: {
							ldstatus:0,
							deviceId :deviceId,
										
						},
					}).then((res)=>{
						console.log('LED off!')
					})   
				}
			},
			
			
			onFanSwitch01(event) {
				console.log(event.detail.value);
				let sw = event.detail.value;
				if(sw) {
					http({
						method:'GET',
						url: '/greenhouse/updateData',//后端接口地址
						data: {
							motor1:1,
							deviceId: deviceId,
										
						},
					}).then((res)=>{
						console.log('FAN01 on!')
					})   
				}
				else {
					http({
						method:'GET',
						url: '/greenhouse/updateData',//后端接口地址
						data: {
							motor1:0,
							deviceId: deviceId,
										
						},
					}).then((res)=>{
						console.log('FAN01 off!')
					})   
				}
			},
			onFanSwitch02(event) {
				console.log(event.detail.value);
				let sw = event.detail.value;
				if(sw) {
					http({
						method:'GET',
						url: '/greenhouse/updateData',//后端接口地址
						data: {
							motor2:1,
							 deviceId: deviceId,
										
						},
					}).then((res)=>{
						console.log('FAN02 on!')
					})   
				}
				else {
					http({
						method:'GET',
						url: '/greenhouse/updateData',//后端接口地址
						data: {
							motor2:0,
							deviceId: deviceId,
										
						},
					}).then((res)=>{
						console.log('FAN02 off!')
					})   
				}
			},
			Switch(event) {
			  window.location.href = 'http://localhost:8081/#/pages/control/control'; // 跳转到指定页面的路径
				http({
					method:'GET',
					url: '/greenhouse/updateData',//后端接口地址
					data: {
						swi:0,
					},
				}).then((res)=>{
					console.log('open control!')
				})   
			},
		}
	}
</script>

<style>
	.wrapper {
		padding: 30rpx;
	}

	.device-area {
		display: flex;
		justify-content: space-between;
		flex-wrap: wrap;
	}

	.device-cart {
		width: 320rpx;
		height: 150rpx;
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
	
	.device-name{
		text-align: center;
		color: #6d6d6d;
	}
	.device-logo{
		width: 70rpx;
		height: 70rpx;
		margin-top: 10rpx;
	}
	.device-data{
		font-size: 50rpx;
		color: #6d6d6d;
		
	}
</style> -->

<!-- <template>
	<div class="container">
		<div v-if="currentPage === 'control'">
			<h3>自动控制模式</h3><br>
			<label for="deviceSelect">选择设备：</label>
			<select id="deviceSelect" v-model="selectedDevice" class="custom-select">
				<option value="">请选择设备</option>
				<option value="1">设备1</option>
				<option value="0">设备2</option>
			</select>
			<br>
			<br>
			<br>
			<br>
			
			<label for="temp1">温度阈值1：</label>
			<input type="number" v-model="temp1" placeholder="温度阈值1" class="threshold-input" />
			<label for="temp2">温度阈值2：</label>
			<input type="number" v-model="temp2" placeholder="温度阈值2" class="threshold-input" />

			
			<label for="ld">光照阈值：</label>
			<input type="number" v-model="ld" placeholder="光照阈值" class="threshold-input" />
			<button @click="submitThresholds" class="submit-button">提交</button>
			<br>
			<button @click="switchToPress" class="switch-button">跳转到手动控制页面</button>
		</div>


		<div v-if="currentPage === 'press'">
			<view class="wrapper">
				<h3>手动控制模式</h3><br>
				<label for="deviceSelect">选择设备：</label>
				<select id="deviceSelect" v-model="selectedDevice" class="custom-select" @change="handleDeviceChange">
					<option value="">请选择设备</option>
					<option value="1">设备1</option>
					<option value="0">设备2</option>
				</select>
				<br>
				<br>
				<view class="device-area">

					<view class="device-cart">
						<view class="device-info">
							<view class="device-name">LED灯</view>
							<image class="device-logo" src="/static/Led.png"></image>
						</view>
						<switch @change="onLedSwitch" color="#2b9939" :checked="ldstatus" />
					</view>
					<view class="device-cart">
						<view class="device-info">
							<view class="device-name">风扇1</view>
							<image class="device-logo" src="/static/Fan.png"></image>
						</view>
						<switch @change="onFanSwitch01" color="#2b9939" :checked="motor1" />
					</view>

					<view class="device-cart">
						<view class="device-info">
							<view class="device-name">风扇2</view>
							<image class="device-logo" src="/static/Fan.png"></image>
						</view>
						<switch @change="onFanSwitch02" color="#2b9939" :checked="motor2" />
					</view>
				</view>
				<br>
				<button @click="switchToControl" class="switch-button">跳转到自动控制页面</button>
			</view>
			</view>
		</div>
	</div>
</template>

<script>
	import {
		http
	} from '../../utils/http';
	export default {
		data() {
			return {
				temp1: null,
				temp2: null,
				ld: null,
				deviceId: null,
				currentPage: 'press', // 当前页面
				ldstatus: false,
				motor1: false,
				motor2: false,
				swi: false,
				selectedDevice: '1',

			};
		},
		methods: {
			submitThresholds() {
				http({
					method: 'GET',
					url: '/greenhouse/updateData', //后端接口地址
					data: {
						temp1: this.temp1,
						temp2: this.temp2,
						ld: this.ld,
						deviceId: this.handleDeviceChange(),
					},
				}).then((res) => {
					console.log('success')
				})
			},
			handleDeviceChange(event) {
				let deviceId = '';
				if (this.selectedDevice === '1') {
					deviceId = '1';
				} else if (this.selectedDevice === '0') {
					deviceId = '0';
				}
				return deviceId;
			},

			onLedSwitch(event) {
				console.log(event.detail.value);
				let sw = event.detail.value;
				// const deviceId=this.handleDeviceChange();
				if (sw) {

					http({
						method: 'GET',
						url: '/greenhouse/updateData', //后端接口地址
						data: {
							ldstatus: 1,
							deviceId: this.handleDeviceChange(),

						},
					}).then((res) => {
						console.log('LED on!')
					})

				} else {
					http({
						method: 'GET',
						url: '/greenhouse/updateData', //后端接口地址
						data: {
							ldstatus: 0,
							deviceId: this.handleDeviceChange(),

						},
					}).then((res) => {
						console.log('LED off!')
					})
				}
			},


			onFanSwitch01(event) {
				console.log(event.detail.value);
				let sw = event.detail.value;

				if (sw) {
					http({
						method: 'GET',
						url: '/greenhouse/updateData', //后端接口地址
						data: {
							motor1: 1,
							deviceId: this.handleDeviceChange(),

						},
					}).then((res) => {
						console.log('FAN01 on!')
					})
				} else {
					http({
						method: 'GET',
						url: '/greenhouse/updateData', //后端接口地址
						data: {
							motor1: 0,
							deviceId: this.handleDeviceChange(),

						},
					}).then((res) => {
						console.log('FAN01 off!')
					})
				}
			},
			onFanSwitch02(event) {
				console.log(event.detail.value);
				let sw = event.detail.value;

				if (sw) {
					http({
						method: 'GET',
						url: '/greenhouse/updateData', //后端接口地址
						data: {
							motor2: 1,
							deviceId: this.handleDeviceChange(),

						},
					}).then((res) => {
						console.log('FAN02 on!')
					})
				} else {
					http({
						method: 'GET',
						url: '/greenhouse/updateData', //后端接口地址
						data: {
							motor2: 0,
							deviceId: this.handleDeviceChange(),

						},
					}).then((res) => {
						console.log('FAN02 off!')
					})
				}
			},
			switchToControl() {
				// 切换到自动控制页面
				// 向后端发送swi:0
				http({
					method: 'GET',
					url: '/greenhouse/updateData', //后端接口地址
					data: {
						swi: 0,
						deviceId: this.handleDeviceChange(),
					},
				}).then((res) => {
					console.log('success')
				})

				this.currentPage = 'control';
			},
			// switchToControl() {
			//   // 切换到自动控制页面
			//   this.currentPage = 'control';
			// },
			switchToPress() {
				// 切换到手动控制页面
				http({
					method: 'GET',
					url: '/greenhouse/updateData', //后端接口地址
					data: {
						swi: 1,
						deviceId: this.handleDeviceChange(),
					},
				}).then((res) => {
					console.log('success')
				})

				this.currentPage = 'press';
			},
		},
	};
</script>

<style scoped>
	.container {
		display: flex;
		flex-direction: column;
		align-items: center;
	}

	h3 {
		text-align: center;
	}

	.custom-select {
		font-size: 16px;
	}

	.custom-select option {
		font-size: 30px;
	}

	.threshold-input {
		margin-bottom: 15px;
		padding: 4px;
		border: 1px solid #ccc;
		border-radius: 5px;
	}

	.submit-button {
		padding: 1px 35px;
		background-color: #007bff;
		color: #fff;
		border: none;
		border-radius: 5px;
		cursor: pointer;
	}

	.wrapper {
		padding: 30rpx;
	}

	.device-area {
		display: flex;
		justify-content: space-between;
		flex-wrap: wrap;
	}

	.device-cart {
		width: 320rpx;
		height: 150rpx;
		border-radius: 30rpx;
		margin-top: 30rpx;
		display: flex;
		justify-content: space-around;
		align-items: center;
	
		box-shadow: 0 0 15rpx #ccc;
	}

	.device-info {
		font-size: 20rpx;
		
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
</style> -->

<template>
	<div class="container">
		<div v-if="currentPage === 'control'">
			<h3>自动控制模式</h3><br>
			<label for="deviceId">默认输入设备号为1，请手动输入设备号：</label>
			<input type="number" v-model="deviceId" placeholder="输入对应数字选择设备" class="input-border" />
			<br>

			<label for="temp1">温度阈值1：</label>
			<input type="number" v-model="temp1" placeholder="温度阈值1" class="threshold-input" />
			<label for="temp2">温度阈值2：</label>
			<input type="number" v-model="temp2" placeholder="温度阈值2" class="threshold-input" />


			<label for="ld">光照阈值：</label>
			<input type="number" v-model="ld" placeholder="光照阈值" class="threshold-input" />
			<button @click="submitThresholds" class="submit-button">提交</button>
			<br>
			<button @click="switchToPress" class="switch-button">跳转到手动控制页面</button>
		</div>


		<div v-if="currentPage === 'press'">
			<view class="wrapper">
				<h3>手动控制模式</h3><br>
				<label for="deviceId">默认输入设备号为1，请手动输入设备号：</label>
				<input type="number" v-model="deviceId" placeholder="输入对应数字选择设备" class="input-border" />
				<view class="device-area">
					<!-- <view class="device-cart">
						<view class="device-info">
							<view class="device-name">LED灯</view>
							<image class="device-logo" src="/static/Led.png"></image>
						</view>
						<switch @change="onLedSwitch" color="#2b9939" :checked="ldstatus" />
					</view>
					<view class="device-cart">
						<view class="device-info">
							<view class="device-name">风扇1</view>
							<image class="device-logo" src="/static/Fan.png"></image>
						</view>
						<switch @change="onFanSwitch01" color="#2b9939" :checked="motor1" />
					</view>

					<view class="device-cart">
						<view class="device-info">
							<view class="device-name">风扇2</view>
							<image class="device-logo" src="/static/Fan.png"></image>
						</view>
						<switch @change="onFanSwitch02" color="#2b9939" :checked="motor2" />
					</view> -->
					<view class="device-cart">
						<view class="device-info">
							<view class="device-name">照明</view>
							<image class="device-logo" src="/static/Light.png"></image>
						</view>
						<switch @change="onLightSwitch" color="#2b9939" :checked="light1" />
					</view>
					<view class="device-cart">
						<view class="device-info">
							<view class="device-name">通风</view>
							<image class="device-logo" src="/static/Fan.png"></image>
						</view>
						<switch @change="onVentSwitch" color="#2b9939" :checked="vent1" />
					</view>
					<view class="device-cart">
						<view class="device-info">
							<view class="device-name">灌溉</view>
							<image class="device-logo" src="/static/irr.png"></image>
						</view>
						<switch @change="onIrrSwitch" color="#2b9939" :checked="irr1" />
					</view>
					<view class="device-cart">
						<view class="device-info">
							<view class="device-name">大棚卷帘</view>
							<image class="device-logo" src="/static/JL.png"></image>
						</view>
						<switch @change="onRollSwitch" color="#2b9939" :checked="roll" />
					</view>
				</view>
				<br>
				<button @click="switchToControl" class="switch-button">跳转到自动控制页面</button>
			</view>
			</view>
		</div>
	</div>
</template>

<script>
	import {
		http
	} from '../../utils/http';
	export default {
		data() {
			return {
				temp1: null,
				temp2: null,
				ld: null,
				deviceId: '1',
				currentPage: 'press', // 当前页面
				// ldstatus: false,
				// motor1: false,
				// motor2: false,
				// swi: false,
				//selectedDevice: '1',
				light1: false,
				vent1: false,
				irr1: false,
				roll: false,

			};
		},
		methods: {
			submitThresholds() {
				http({
					method: 'GET',
					url: '/greenhouse/updateData', //后端接口地址
					data: {
						temp3: this.temp1,
						temp4: this.temp2,
						ld: this.ld,
						deviceId: this.deviceId,
					},
				}).then((res) => {
					console.log('success')
				})
			},

			onLightSwitch(event) {
				console.log(event.detail.value);
				let sw = event.detail.value;
				// const deviceId=this.handleDeviceChange();
				if (sw) {

					http({
						method: 'GET',
						url: '/greenhouse/updateData', //后端接口地址
						data: {
							light1: 1,
							deviceId: this.deviceId,

						},
					}).then((res) => {
						console.log('开启照明')
					})

				} else {
					http({
						method: 'GET',
						url: '/greenhouse/updateData', //后端接口地址
						data: {
							light1: 0,
							deviceId: this.deviceId,

						},
					}).then((res) => {
						console.log('关闭照明')
					})
				}
			},


			onVentSwitch(event) {
				console.log(event.detail.value);
				let sw = event.detail.value;

				if (sw) {
					http({
						method: 'GET',
						url: '/greenhouse/updateData', //后端接口地址
						data: {
							vent1: 1,
							deviceId: this.deviceId,

						},
					}).then((res) => {
						console.log('开启通风')
					})
				} else {
					http({
						method: 'GET',
						url: '/greenhouse/updateData', //后端接口地址
						data: {
							vent1: 0,
							deviceId: this.deviceId,

						},
					}).then((res) => {
						console.log('关闭通风')
					})
				}
			},
			onIrrSwitch(event) {
				console.log(event.detail.value);
				let sw = event.detail.value;

				if (sw) {
					http({
						method: 'GET',
						url: '/greenhouse/updateData', //后端接口地址
						data: {
							irr1: 1,
							deviceId: this.deviceId,

						},
					}).then((res) => {
						console.log('开启灌溉')
					})
				} else {
					http({
						method: 'GET',
						url: '/greenhouse/updateData', //后端接口地址
						data: {
							irr1: 0,
							deviceId: this.deviceId,

						},
					}).then((res) => {
						console.log('关闭灌溉')
					})
				}
			},
			onRollSwitch(event) {
				console.log(event.detail.value);
				let sw = event.detail.value;
			
				if (sw) {
					http({
						method: 'GET',
						url: '/greenhouse/updateData', //后端接口地址
						data: {
							roll: 1,
							deviceId: this.deviceId,
			
						},
					}).then((res) => {
						console.log('开启卷帘')
					})
				} else {
					http({
						method: 'GET',
						url: '/greenhouse/updateData', //后端接口地址
						data: {
							roll: 0,
							deviceId: this.deviceId,
			
						},
					}).then((res) => {
						console.log('关闭卷帘')
					})
				}
			},
			switchToControl() {
				// 切换到自动控制页面
				// 向后端发送swi:0
				http({
					method: 'GET',
					url: '/greenhouse/updateData', //后端接口地址
					data: {
						swi: 0,
						deviceId: this.deviceId,
					},
				}).then((res) => {
					console.log('success')
				}) 

				this.currentPage = 'control';
			},
			// switchToControl() {
			//   // 切换到自动控制页面
			//   this.currentPage = 'control';
			// },
			switchToPress() {
				// 切换到手动控制页面
				http({
					method: 'GET',
					url: '/greenhouse/updateData', //后端接口地址
					data: {
						swi: 1,
						deviceId: this.deviceId,
					},
				}).then((res) => {
					console.log('success')
				}) 

				this.currentPage = 'press';
			},
		},
	};
</script>

<style scoped>
	.container {
		display: flex;
		flex-direction: column;
		align-items: center;
	}

	h3 {
		text-align: center;
	}

	.custom-select {
		font-size: 16px;
	}

	.custom-select option {
		font-size: 30px;
	}

	.threshold-input {
		margin-bottom: 15px;
		padding: 4px;
		border: 1px solid #ccc;
		border-radius: 5px;
	}

	.submit-button {
		padding: 1px 35px;
		background-color: #007bff;
		color: #fff;
		border: none;
		border-radius: 5px;
		cursor: pointer;
	}

	.wrapper {
		padding: 30rpx;
	}

	.device-area {
		display: flex;
		justify-content: space-between;
		flex-wrap: wrap;
	}

	.device-cart {
		width: 320rpx;
		height: 150rpx;
		border-radius: 30rpx;
		margin-top: 30rpx;
		display: flex;
		justify-content: space-around;
		align-items: center;

		box-shadow: 0 0 15rpx #ccc;
	}

	.device-info {
		font-size: 20rpx;

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

	.input-border {
		border: 1px solid #000000;
		/* 边框宽度和颜色 */
		padding: 5px;
		/* 内边距 */
		height: 20px;
		width: 328px;
	}
</style>