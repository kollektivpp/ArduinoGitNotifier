var btSerial = new (require('bluetooth-serial-port')).BluetoothSerialPort(),
    btModuleName = 'HC-06',
    endOfMessageDelimiter = '%%%',
    concatString = '';

var onData = function(buffer) {
    var string = buffer.toString('utf-8');

    if (string.indexOf(endOfMessageDelimiter) !== -1) {
        concatString += string.replace(endOfMessageDelimiter, '');
        console.log(concatString);
    } else {
        concatString += string;
    }
};

var writeString = function(string) {
    concatString = '';
    btSerial.write(new Buffer(string, 'utf-8'), function(err, bytesWritten) {
        if (err) {
            console.log(err);
        }
    });
};

var connect = function() {
    btSerial.on('found', function(address, name) {
        if (name !== btModuleName) {
            return;
        }
        console.log('Found Device: ' + name);

        btSerial.findSerialPortChannel(address, function(channel) {
            btSerial.connect(address, channel, function() {
                console.log('Connected to Device:' + name);
                btSerial.on('data', onData);
            }, function () {
                console.log('cannot connect to: ' + name);
            });

            // close the connection when you're ready
            btSerial.close();
        });
    });

    btSerial.inquire();
};

exports.connect = connect;
exports.writeString = writeString;
