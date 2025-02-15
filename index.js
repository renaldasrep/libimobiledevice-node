const cp = require('child_process')

exports.id = function(callback) {
	if (typeof callback !== 'function') {
		callback(Error('Callback is not a function'), null)
	} else {
		const child = cp.fork(`${__dirname}/lib/id_worker`)
		child.on('message', data => {
			callback(data)
			child.disconnect()
		})
		return child
	}

	return null
}

exports.info = function(options, callback) {
	if (typeof options === "function") {
		callback = options
		options = null
	}

	options = options || {}

	if (options.constructor.name !== 'Object') {
		callback(Error('Options must be an object'), null)
	} else if (typeof callback !== 'function') {
		callback(Error('Callback is not a function'), null)
	} else {
		const child = cp.fork(`${__dirname}/lib/info_worker`)
		child.send(options)
		child.on('message', res => {
			callback(res.err, res.data)
			child.disconnect()
		})
		return child
	}

	return null
}

exports.pair = function(command, callback) {
	const child = cp.fork(`${__dirname}/lib/pair_worker`)
	child.send(command)
	child.on('message', res => {
		callback(res.err, res.data)
		child.disconnect()
	})
	return child
}