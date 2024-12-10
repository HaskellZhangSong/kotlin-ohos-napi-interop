import { hilog } from '@kit.PerformanceAnalysisKit';
import testNapi from 'libentry.so';

type Ptr = Object

class KNBridgeObject {
  private _ptr_native: Ptr;

  public constructor() {
    this._ptr_native = testNapi.ObjBridge_create();
  }

  public foo(x : string) : void {
    return testNapi.ObjBridge_foo(this._ptr_native, x);
  }
  public bar(): string {
    return testNapi.ObjBridge_bar(this._ptr_native);
  }
}

@Entry
@Component
struct Index {
  @State message: string = 'Hello World';

  build() {
    Row() {
      Column() {
        Text(this.message)
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            let obj = new KNBridgeObject();
            hilog.info(0x0000, 'testTag', '%s', obj.foo("0123456789ABCDEF"))
            hilog.info(0x0000, 'testTag', '%s', obj.bar())
            // hilog.info(0x0000, 'testTag', 'Test NAPI 2 + 3 = %{public}d', testNapi.inc(2))

          })
      }
      .width('100%')
    }
    .height('100%')
  }
}

