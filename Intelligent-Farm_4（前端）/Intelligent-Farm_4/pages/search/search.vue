<!-- <template>

	<div class="container">
		<div class="form-group">
			<label for="sensorSelect">选择传感器类型：</label>
			<select id="sensorSelect" v-model="selectedSensor" class="custom-select">
				<option value="">请选择传感器类型</option>
				<option value="temperature">温度传感器</option>
				<option value="humidity">湿度传感器</option>
				<option value="light">光敏传感器</option>
			</select>
		</div>

		<div class="form-group">
			<label for="deviceSelect">选择设备：</label>
			<select id="deviceSelect" v-model="selectedDevice" class="custom-select" @change="updateDeviceId">
				<option value="1">设备1</option>
				<option value="0">设备2</option>
			</select>
		</div>
		
		<div class="form-group">
			<view class="inputstyle">
				<label for="timeSelect">选择起始时间：</label>
			</view>
			 <view class="example-body">
			<uni-datetime-picker type="datetime" v-model="startTime"/> 
			</view>		 		
		</div>

		<button @click="fetchSensorData">查询历史数据</button>

		<div>
			<h4>查询结果：</h4>
			<ul>
				<li v-for="(data, index) in nowsensorData" :key="index">{{ data.data }} {{ data.time}}</li>
			</ul>
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
				selectedSensor: '', // 选中的传感器类型
				selectedDevice: '', 
				timeSelect: '', // 起始时间
				sensorData: [], // 查询到的传感器数据
				startTime: '',
				// changeLog:'',
			};
		},
		methods: {
			fetchSensorData() {
				// 根据选中的传感器类型和起始时间，向后端发起对应的接口请求获取数据
				http({
					method: 'GET',
					url: '/greenhouse/transAll2', //后端接口地址
					data: {
						startTime: this.startTime,
						deviceId: this.deviceId,
					},
				}).then((res) => {
					this.sensorData = [...res.data.greenHouse];
					console.log(this.sensorData)
				}).catch((err) => {
					console.log(err)
				})
			},
			updateDeviceId() {
							// 根据选中的设备更新 deviceId 的值
					if (this.selectedDevice === '1') {
						this.deviceId = 1;
						} else if (this.selectedDevice === '0') {
							this.deviceId = 0;
						}
					}
		},
		computed: {
			nowsensorData: function() {
				if (this.selectedSensor === 'temperature') {
					return this.sensorData.map(obj => {
						return {
							data: obj.temp,
							time: obj.time
						}
					});
				} else if (this.selectedSensor === 'humidity') {
					return this.sensorData.map(obj => {
						return {
							data: obj.humi,
							time: obj.time
						}
					});
				} else if (this.selectedSensor === 'light') {
					return this.sensorData.map(obj => {
						return {
							data: obj.ld,
							time: obj.time
						}
					});
				}
			}
		}

	};
</script>

<style scoped>
	.container {
		max-width: 600px;
		margin: 0 auto;
		//padding: 30px;
		padding: 10px;
	}

	.form-group {
		margin-bottom: 10px;
	}

	.data-container {
		margin-top: 40px;
	}

	.inputstyle {
		color: #000000;
	}

	.example-body {
		background-color: #fff;
		//padding: 10px;
		padding: 0px;
	}

	.custom-select {
		width: 340px;
		height: 35px;
		font-size: 3px;
	}
	.custom-select option{
		font-size: 30px;
	}
</style> -->
<!-- <template>
  <div class="container">
    <div class="form-group">
      <label for="sensorInput">选择传感器类型：</label>
      <div>
        <div
          v-for="sensor in sensors"
          :key="sensor.value"
          @click="selectSensor(sensor.value)"
          :class="{ 'sensor-option': true, 'selected': selectedSensor === sensor.value }"
        >
          {{ sensor.label }}
        </div>
      </div>
    </div>
    <div class="form-group">
      <label for="deviceId">请手动输入设备号：</label>
      <input type="number" v-model="deviceId" placeholder="输入对应数字选择设备" class="input-border" />
      <br>
    </div>

    <div class="form-group">
      <view class="inputstyle">
        <label for="timeSelect">选择起始时间：</label>
      </view>
      <view class="example-body">
        <uni-datetime-picker type="datetime" v-model="startTime" />
      </view>
    </div>

    <button @click="fetchSensorData">查询历史数据</button>

    <div class="chart-container">
      <h4>查询结果：</h4>
      <div ref="sensorChart" style="width: 100%; height: 400px;"></div>
    </div>

    <div>
      <ul>
        <li v-for="(data, index) in nowsensorData" :key="index">{{ data.data }} {{ data.time}}</li>
      </ul>
    </div>
  </div>
</template>

<script>
import * as echarts from 'echarts';
import { http } from '../../utils/http';

export default {
  data() {
    return {
      selectedSensor: '', // 选中的传感器类型
      deviceId: '',
      startTime: '',
       sensorData: [],
      sensorChart: null, // 存储图表对象 
      sensors: [
        {
          label: '温度1传感器',
          value: 'temperature'
        },
        {
          label: '温度2传感器',
          value: 'humidity'
        },
        {
          label: '光敏传感器',
          value: 'light'
        },
      ],
    };
  },
 
  computed: {
    nowsensorData() {
      if (this.selectedSensor === 'temperature') {
        return this.sensorData.map(obj => {
          return {
            data: obj.temp1,
            time: obj.time
          }
        });
      } else if (this.selectedSensor === 'humidity') {
        return this.sensorData.map(obj => {
          return {
            data: obj.temp2,
            time: obj.time
          }
        });
      } else if (this.selectedSensor === 'light') {
        return this.sensorData.map(obj => {
          return {
            data: obj.ld,
            time: obj.time
          }
        });
      }
      return [];
    }
  },
  methods: {
    selectSensor(sensor) {
      this.selectedSensor = sensor;
    },
    fetchSensorData() {
      http({
        method: 'GET',
        url: '/greenhouse/transAll2', // 后端接口地址
        data: {
          startTime: this.startTime,
          deviceId: this.deviceId,
        },
      })
      .then((res) => {
        this.sensorData = [...res.data.greenHouse];
        this.renderChart(); // 渲染折线图
        console.log(this.sensorData)
      })
      .catch((err) => {
        console.log(err)
      })
    },
    renderChart() {
      if (!this.sensorChart) {
        // 初始化图表对象
        this.sensorChart = echarts.init(this.$refs.sensorChart);
      }
    
      const xAxisData = this.sensorData.map(obj => obj.time);
      let yAxisData = [];
      let yAxisName = '';	
      
      // 根据选中的传感器类型设置y轴数据和y轴名称
      if (this.selectedSensor === 'temperature') {
        yAxisData = this.sensorData.map(obj => obj.temp1);
        yAxisName = '温度1';
      } else if (this.selectedSensor === 'humidity') {
        yAxisData = this.sensorData.map(obj => obj.temp2);
        yAxisName = '温度2';
      } else if (this.selectedSensor === 'light') {
        yAxisData = this.sensorData.map(obj => obj.ld);
        yAxisName = '光敏';
      }
      
      const option = {
        xAxis: {
          type: 'category',
          data: xAxisData,
        },
        yAxis: {
          type: 'value',
          name: yAxisName,
        },
        series: [{
          type: 'line',
          data: yAxisData,
        }],
      };
      
      // 使用配置项渲染图表
      this.sensorChart.setOption(option);
    },
  },
};
</script>
 -->
<template>
  <div class="container">
    <div class="form-group">
      <label for="sensorInput">选择传感器类型：</label>
      <div>
        <div
          v-for="sensor in sensors"
          :key="sensor.value"
          @click="selectSensor(sensor.value)"
          :class="{ 'sensor-option': true, 'selected': selectedSensor === sensor.value }"
        >
          {{ sensor.label }}
        </div>
      </div>
    </div>
    <div class="form-group">
      <label for="deviceId">请手动输入设备号：</label>
      <input type="number" v-model="deviceId" placeholder="输入对应数字选择设备" class="input-border" />
      <br>
    </div>

    <div class="form-group">
      <view class="inputstyle">
        <label for="timeSelect">选择起始时间：</label>
      </view>
      <view class="example-body">
        <uni-datetime-picker type="datetime" v-model="startTime" />
      </view>
    </div>

    <button @click="fetchSensorData">查询历史数据</button>

    <div class="chart-container">
      <h4>查询结果：</h4>
      <div ref="sensorChart" style="width: 100%; height: 400px;"></div>
    </div>

    <div>
      <ul>
        <li v-for="(data, index) in nowsensorData" :key="index">{{ data.data }} {{ data.time}}</li>
      </ul>
    </div>
  </div>
</template>

<script>
import { http } from '../../utils/http';
import * as echarts from 'echarts';

export default {
  data() {
    return {
      selectedSensor: '', // 选中的传感器类型
      deviceId: '',
      startTime: '',
      sensorData: [],
      sensors: [
        {
          label: '温度1传感器',
          value: 'temperature'
        },
        {
          label: '温度2传感器',
          value: 'humidity'
        },
        {
          label: '光敏传感器',
          value: 'light'
        },
      ],
    };
  },

  computed: {
    nowsensorData() {
      if (this.selectedSensor === 'temperature') {
        return this.sensorData.map(obj => {
          return {
            data: obj.temp1,
            time: obj.time
          }
        });
      } else if (this.selectedSensor === 'humidity') {
        return this.sensorData.map(obj => {
          return {
            data: obj.temp2,
            time: obj.time
          }
        });
      } else if (this.selectedSensor === 'light') {
        return this.sensorData.map(obj => {
          return {
            data: obj.ld,
            time: obj.time
          }
        });
      }
      return [];
    }
  },
  methods: {
    selectSensor(sensor) {
      this.selectedSensor = sensor;
    },
    fetchSensorData() {
      http({
        method: 'GET',
        url: '/greenhouse/transAll2', // 后端接口地址
        data: {
          startTime: this.startTime,
          deviceId: this.deviceId,
        },
      })
      .then((res) => {
        this.sensorData = [...res.data.greenHouse];
        this.renderChart(); // 渲染折线图
        console.log(this.sensorData)
      })
      .catch((err) => {
        console.log(err)
      })
    },
    renderChart() {
      const chartContainer = this.$refs.sensorChart;
      if (chartContainer) {
        // 清空容器
        while (chartContainer.firstChild) {
          chartContainer.removeChild(chartContainer.firstChild);
        }

        const xAxisData = this.sensorData.map(obj => obj.time);
        let yAxisData = [];
        let yAxisName = '';

        // 根据选中的传感器类型设置y轴数据和y轴名称
        if (this.selectedSensor === 'temperature') {
          yAxisData = this.sensorData.map(obj => obj.temp1);
          yAxisName = '温度1';
        } else if (this.selectedSensor === 'humidity') {
          yAxisData = this.sensorData.map(obj => obj.temp2);
          yAxisName = '温度2';
        } else if (this.selectedSensor === 'light') {
          yAxisData = this.sensorData.map(obj => obj.ld);
          yAxisName = '光敏';
        }

        const option = {
          xAxis: {
            type: 'category',
            data: xAxisData,
          },
          yAxis: {
            type: 'value',
            name: yAxisName,
          },
          series: [{
            type: 'line',
            data: yAxisData,
          }],
        };

        // 使用Render.js渲染图表
		    if (chart && !chart.isDisposed()) {
		          chart.dispose();
		        }

		const chart = echarts.init(chartContainer);
		chart.setOption(option);
      /*  const chart = new window.RenderChart(chartContainer);
        chart.render(option); */
      }
    },
  },
};
</script>


<!-- <template>
	<div class="container">
		<div class="form-group">
			<label for="sensorInput">输入传感器类型：</label>
			<input type="text" v-model="selectedSensor" id="sensorInput" class="input-border" placeholder="输入传感器类型" />
		</div>

		<div class="form-group">
			<label for="deviceIdInput">请手动输入设备号：</label>
			<input type="number" v-model="deviceId" id="deviceIdInput" placeholder="输入对应数字选择设备" class="input-border" />
		</div>

		<div class="form-group">
			<view class="inputstyle">
				<label for="timeSelect">选择起始时间：</label>
			</view>
			<view class="example-body">
				<uni-datetime-picker type="datetime" v-model="startTime" />
			</view>
		</div>

		<button @click="fetchSensorData">查询历史数据</button>

		<div class="chart-container">
			<h4>查询结果：</h4>
			<div id="sensorChart" style="width: 100%; height: 400px;"></div>
		</div>
	
		<div>
			<ul>
				<li v-for="(data, index) in nowsensorData" :key="index">{{ data.data }} {{ data.time}}</li>
			</ul>
		</div>
	</div>
</template>

<script>
	import * as echarts from 'echarts';
	import {
		http
	} from '../../utils/http';
	export default {
		updated() {
			try {
				
				this.renderChart();
				
			} catch (error) {
				console.error('渲染图表时出错：', error);
			}
		},
		data() {
			return {
				selectedSensor: '', // 选中的传感器类型
				selectedDevice: '',
				timeSelect: '', // 起始时间
				sensorData: [], // 查询到的传感器数据
				startTime: '',
				sensorChart: null, // 存储图表对象
				chartContainer: null,
				deviceId: '',
				// changeLog:'',
			};
		},
		methods: {
			fetchSensorData() {
				// 根据选中的传感器类型和起始时间，向后端发起对应的接口请求获取数据
				http({
						method: 'GET',
						url: '/greenhouse/transAll2', //后端接口地址
						data: {
							startTime: this.startTime,
							deviceId: this.deviceId,
						},
					})
					.then((res) => {
						this.sensorData = [...res.data.greenHouse];
						this.renderChart(); // 渲染折线图
						console.log(this.sensorData);
					})
					.catch((err) => {
						console.log(err);
					});
			},

			 renderChart() {

				if (!this.sensorChart) {
					// 初始化图表对象
					this.sensorChart = echarts.init(document.getElementById('sensorChart'));
					
				} 

				// 准备图表数据
				const xAxisData = this.sensorData.map((obj) => obj.time);
				let yAxisData = [];
				let yAxisName = '';

				// 根据选中的传感器类型设置y轴数据和y轴名称
				if (this.selectedSensor === 'temperature') {
					yAxisData = this.sensorData.map((obj) => obj.temp);
					yAxisName = '温度';
				} else if (this.selectedSensor === 'humidity') {
					yAxisData = this.sensorData.map((obj) => obj.humi);
					yAxisName = '湿度';
				} else if (this.selectedSensor === 'light') {
					yAxisData = this.sensorData.map((obj) => obj.ld);
					yAxisName = '光敏';
				}

				// 设置图表配置项
				const option = {
					xAxis: {
						type: 'category',
						data: xAxisData,
					},
					yAxis: {
						type: 'value',
						name: yAxisName,
					},
					series: [{
						type: 'line',
						data: yAxisData,
					}, ],
				};

				// 使用配置项渲染图表
				this.sensorChart.setOption(option);

				// 在窗口大小改变时重新绘制图表
				window.addEventListener('resize', () => {
					this.sensorChart.resize();
				});
			},
		},
		computed: {
			nowsensorData: function() {
				if (this.selectedSensor === 'temperature') {
					return this.sensorData.map((obj) => {
						return {
							data: obj.temp,
							time: obj.time,
						};
					});
				} else if (this.selectedSensor === 'humidity') {
					return this.sensorData.map((obj) => {
						return {
							data: obj.humi,
							time: obj.time,
						};
					});
				} else if (this.selectedSensor === 'light') {
					return this.sensorData.map((obj) => {
						return {
							data: obj.ld,
							time: obj.time,
						};
					});
				}
			},
		},
	};
</script> -->

<style scoped>
	
	.sensor-option {
		padding: 5px;
		margin: 5px;
		cursor: pointer;
		background-color:#55aaff ;
		color: #fff;
		border-radius: 10px; /* 添加圆角效果 */
	
		
	}
	
	.selected {
		background-color:#aaaaff ;
		/* 选中状态下为蓝色 */
		 border-radius: 10px; /* 添加圆角效果 */
	}
	.container {
		max-width: 600px;
		margin: 0 auto;
		//padding: 30px;
		padding: 10px;
	}

	.chart-container {
		margin-top: 20px;
	}

	.form-group {
		margin-bottom: 10px;
	}

	.data-container {
		margin-top: 40px;
	}

	.inputstyle {
		color: #000000;
	}

	.example-body {
		background-color: #fff;
		//padding: 10px;
		padding: 0px;
	}

	.custom-select {
		width: 340px;
		height: 35px;
		font-size: 3px;
	}

	.custom-select option {
		font-size: 30px;
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