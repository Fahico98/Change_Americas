
<div class="container">
   <div class="form-item form-item-mail form-type-textfield form-group">
      <label class="control-label" for="edit-name">
         Correo Electrónico <span class="form-required" title="Este campo es obligatorio">*</span>
      </label>
      <input class="form-control form-text required" title="dirección de correo electrónico"
         aria-describedby="edit-name-help" data-toggle="tooltip" type="email" id="edit-name" name="name" size="60"
         maxlength="60" placeholder="correo electrónico" value="" require>
      <small id="edit-name-help" class="form-text text-muted">Ingrese su dirección de correo electrónico.</small>
   </div>
   <div class="form-item form-item-pass form-type-password form-group">
      <label class="control-label" for="edit-pass">
         Contraseña <span class="form-required" title="Este campo es obligatorio">*</span>
      </label>
      <input class="form-control form-text required" title="contraseña" aria-describedby="edit-pass-help" data-toggle="tooltip"
         type="password" id="edit-pass" name="pass" size="60" minlength="8" maxlength="14" placeholder="contraseña" require>
      <small id="edit-pass-help" class="form-text text-muted">Ingrese la contraseña correspondiente con su dirección de
          correo</small>
   </div>
   <input type="hidden" name="form_build_id">
   <input type="hidden" name="form_id" value="user_login">
   <div class="form-actions form-wrapper form-group" id="edit-actions">
      <button type="submit" id="edit-submit" name="op" value="Log in" class="btn btn-primary form-submit icon-before">
         <span class="icon glyphicon glyphicon-log-in" aria-hidden="true"></span> Iniciar Sesión
      </button>
   </div>
</div>
