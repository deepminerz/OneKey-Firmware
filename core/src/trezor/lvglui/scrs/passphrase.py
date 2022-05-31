from ..i18n import gettext as _, keys as i18n_keys
from .common import FullSizeWindow, lv
from .components.keyboard import PassphraseKeyboard


class PassphraseRequest(FullSizeWindow):
    def __init__(self, max_len=50):
        super().__init__(_(i18n_keys.TITLE__ENTER_PASSPHRASE), None)
        self.keyboard = PassphraseKeyboard(self, max_len)
        self.keyboard.add_event_cb(self.eventhandler, lv.EVENT.READY, None)

    def eventhandler(self, event_obj):
        input = self.keyboard.ta.get_text()
        if input == "":
            return
        self.channel.publish(input)
        self.keyboard.ta.set_text("")
        self.destory()
        if __debug__:
            print(f"Enter passphrase: == {input}")