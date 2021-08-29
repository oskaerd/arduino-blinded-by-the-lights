class UartPackage:
    def __init__(self, data=[]):
        self.tx_data = bytes(data)
        self.rx_data = bytes([])

    def set_data(self, data):
        if len(data) != 4:
            # todo error here
            return
        self.tx_data = bytes(data)

    def get_received_data(self):
        return self.rx_data
