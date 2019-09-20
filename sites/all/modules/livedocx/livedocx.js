(function($){
  Drupal.behaviors.liveDocx = {
    attach: function(context, settings){
      if(settings.liveDocX)
        this.attachMergeFieldSelects(settings.liveDocX.selectValues);
      this.attachEntityTypeSelect();
    },
    attachMergeFieldSelects: function(selectValues){
      var eventData = {
        previous: '',
        selectOptions: {},
        that: this
      };
      this.buildSelectOptions(selectValues, eventData);
      $('.livedocx-mergefield-select').focus(eventData, this.mergeFieldSelectFocus).change(eventData, this.mergeFieldSelectChange);
    },
    buildSelectOptions: function(values, eventData){
      var option;
      $.each(values, function(index, element){
        option = $(document.createElement('option')).attr('value', index).text(element);
        eventData.selectOptions[index] =  option;
      });
    },
    mergeFieldSelectFocus: function(eventObj){
      eventObj.data.previous = this.value;
    },
    mergeFieldSelectChange: function(eventObj){
      var current = this.value,
      $selects = $(".livedocx-mergefield-select");
      if(eventObj.data.previous !== 'none'){
        $selects.each(function(index, element){
          eventObj.data.that.rebuildSelect(element, eventObj.data.selectOptions, $selects);
        });
      }
      if(current !== 'none'){
        $selects.not(this).children("option[value='" + current + "']").remove();
      }
    },
    rebuildSelect: function(selectObj, selectOptions, $selects){
      var keySelected = selectObj.value,
      $selectObj = $(selectObj),
      availVals = [],
      elementClone,
      elementValue;
      $.each($selects.children('option').not(':selected'), function(index, value){
        if(this.value !== 'none' && $.inArray(this.value, availVals) === -1){
          availVals.push(this.value);
        }
      });
      $selectObj.empty();
      $.each(selectOptions, function(index, element){
        elementValue = element.attr('value');
        if(elementValue === 'none' || $.inArray(elementValue, availVals) !== -1 || elementValue === keySelected){
          elementClone = element.clone();
          if(index === keySelected){
            elementClone.attr('selected', 'selected');
          }
          $selectObj.append(elementClone);
        }
      });
    },
    attachEntityTypeSelect: function(){
      $('.livedocx-entity-select').change(function(){
        if($(this).attr('value') === 'none'){
          $(this).parent().parent().next().next().empty().append('&nbsp;');
        }
      });
    }
  };
})(jQuery);